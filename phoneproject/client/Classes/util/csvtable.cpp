#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include "csvtable.h"

void cb1(void* s, size_t len, void* data)
{
    csvtable* ct = (csvtable*)data;
    ct->fields_count();
    std::string str((char*)s, len);
    // std::cout<<"cb1:"<<len;
    if (!ct->havetitle())
    {
        // \u5904\u7406titlemap
        // std::cout<<" cb11:"<<str<<"\n";
        ct->titlemap.insert(std::make_pair(str,ct->cur_col++));
    }
    else
    {
        // \u9996\u5148\u68C0\u67E5\u6E38\u6807
        if (ct->cur_col == ct->columns())
        {
            ct->cur_col = 0;
        }

        // std::cout<<" cur_col="<<ct->cur_col<<" cb12:"<<str<<'\n';

        // \u8D4B\u503C
        *((ct->keylist[ct->keylist.size()-1])+ct->cur_col) = str;

        // std::cout<<*((ct->keylist[ct->keylist.size()-1])+ct->cur_col)<<std::endl ;

        ct->cur_col++; // \u6700\u540E\u79FB\u52A8\u6E38\u6807
    }
}

void cb2(int c, void* data)
{
    csvtable* ct = (csvtable*)data;
    ct->rows_count();
    // std::cout<<"cb2\n";
    if (!ct->havetitle())
    {
        // csv\u8868\u7ED3\u6784\u7B2C\u4E00\u884C\u662Fcloumn name \u6240\u4EE5\u53BB\u6389\u9019\u4E00\u884C\u7684\u8A08\u6578
        ct->rows_count(-1);
        // \u7B2C\u4E00\u6B21\u6267\u884Ccb2\uFF0C\u6B64\u65F6\u7684field\u8BA1\u6570\u5C31\u662F\u5217\u6570
        ct->settitle(true);
        ct->set_columns(ct->fields());
    }
    ct->keylist.push_back(new std::string[ct->columns()]);
    // std::cout<<"new"<<ct->keylist.size()<<std::endl;
}

static int is_space(unsigned char c)
{
    if (c == CSV_SPACE || c == CSV_TAB) return 1;
    return 0;
}

static int is_term(unsigned char c)
{
    if (c == CSV_CR || c == CSV_LF) return 1;
    return 0;
}

csvtable::csvtable()
{
    _fields = 0;
    _rows = 0;
    fcb1 = 0;
    fcb2 = 0;
    _options = 0;
    _btitle = false;
    cur_col = 0;
}

// \u91CA\u653E\u8D44\u6E90
csvtable::~csvtable()
{
    // \u91CA\u653Ekeylist new\u51FA\u6765\u7684string\u6570\u7EC4
    std::vector< std::string* >::iterator it;
    for (it=keylist.begin(); it!=keylist.end(); ++it)
    {
        // std::string* p = *it;
        delete [](*it);
    }
}

int csvtable::Init(const char* filename,
                   int  table_type,
                   void (*fcb1)(void *, size_t, void *),
                   void (*fcb2)(int, void *))
{
    if (filename == 0) return -1;
    this->table_type = table_type;
    this->fcb1 = fcb1;
    this->fcb2 = fcb2;
    _filename = filename;
    // \u68C0\u6D4B\u6587\u4EF6\u662F\u5426\u5B58\u5728
    std::ifstream infile(filename);
    if (!infile)
    {
        return -2;
    }
    if (csv_init(&_parser, _options) != 0)
    {
        return -3;
    }
    // \u6DFB\u52A0\u7A7A\u767D\u548C\u7ED3\u675F\u7B26\u7684\u5B9A\u4E49
    csv_set_space_func(&_parser, is_space);
    csv_set_term_func(&_parser, is_term);
    return 0;
}


int csvtable:: read(const char* zSql)
{
    // \u4E0D\u53EF\u4EE5\u91CD\u590D\u8BFB
    if (havetitle())
        return -6;
    FILE *fp;
    fp = fopen(_filename.c_str(), "rb");
    if (fp)
    {
        const int readsize = 8192;
        char line[readsize];
        size_t len;
        // magic word check
        if (!fgets(line, readsize, fp))
        {
            return -1;
        }
        if (strncmp(line, "\"FCTB1.00",strlen("\"FCTB1.00")) != 0
                && strncmp(line, "\"\"\"FCTB1.00",
                           strlen("\"\"\"FCTB1.00")) !=0
                && strncmp(line, "FCTB1.00",
                           strlen("FCTB1.00")) !=0 )
        {
            std::cout<<"magic word check failed."<<std::endl;
            return -2;
        }

        // ignore Chinese comment
        if (!fgets(line, readsize, fp))
        {
            return -6;
        }


        /* \u91CD\u70B9\u5728\u8FD9\u91CC*/
        while ((len = fread(line, 1, readsize, fp)) > 0)
        {
            if (csv_parse(&_parser, line, len, fcb1, fcb2, this)!= len)
            {
                // error occur\uFF0C\u7ACB\u9A6C\u6302\u6389
                fprintf(stderr, "Error while parsing file: %s\n",
                        csv_strerror(csv_error(&_parser)));
                exit(EXIT_FAILURE);
            }
        }

        csv_fini(&_parser, fcb1, fcb2, this);
        csv_free(&_parser);
        fclose(fp);
        // \u5217\u6570\u68C0\u67E5
        if (columns() != _fields / (_rows+1))
        {
            std::cout<<"Error! columns="<<columns()
                     <<" field="<<_fields<<" rows="<<_rows;
            return  -3;
        }
        // \u5220\u9664\u6700\u540E\u4E00\u4E2A\u5206\u914D\u7684\u672A\u4F7F\u7528\u5B58\u50A8
        size_t size = keylist.size();
        if (size>0)
        {
            std::string* p = keylist[size-1];
            delete []p;
            keylist.pop_back();
        }

        // \u5EFA\u7ACB\u7D22\u5F15map
        if (createindex(zSql)<0)
        {
            std::cout<<"createindex failed, return -4"<<std::endl;
            return -4;
        }
        return 0;
    }
    return -5;
}

int csvtable::createindex(const char* zSql)
{
    std::cout<<name()<<" "<<zSql<<"|createindex:"<<table_type;
    switch (table_type)
    {
        // \u552F\u4E00\u7D22\u5F15\u8868\uFF0C\u7528hashmap
    case 0:
    {
        for (size_t i=0; i<keylist.size(); i++)
        {
            keyindexmap.insert(std::make_pair(atoi((*keylist[i]).c_str()), i));
        }
        break;
    }
    // \u4E0D\u552F\u4E00\u7D22\u5F15\uFF0C\u7528hashmultimap
    case 1:
    {
        for (size_t i=0; i<keylist.size(); i++)
        {
            keyindexmultimap.insert(std::make_pair(atoi((*keylist[i]).c_str()), i));
        }
        break;
    }
    default:
    {
        exit(EXIT_FAILURE);
    }
    }
    std::cout<<" done\n ";
    return 0;
}

std::ostream& operator <<(std::ostream& os, csvtable& ct)
{
    os<<ct.name()<<"\ntotal columns="<<ct.columns()<<" rows="<<ct.rows()<<" field="<<ct.fields();
    // \u8F93\u51FAtitle
    if (!ct.titlemap.empty())
    {
        os<<'\n';
        std::map<std::string, int>::iterator it;
        int i=0;
        for (it=ct.titlemap.begin(); it!=ct.titlemap.end(); it++,i++)
        {
            os<<i<<':'<<it->first<<' ';
        }

        switch (ct.table_type)
        {
        case 0:
        {   // index
            HashMap::iterator pos;
            os<<"\nkey:row index\n";
            for (pos=ct.keyindexmap.begin(); pos!=ct.keyindexmap.end(); pos++)
            {
                os<<pos->first<<':'<<pos->second<<'\n';
            }
            // content
            for (size_t key=0; key< ct.keylist.size(); key++)
            {
                os<<"row="<<key;
                for (size_t j=0; j< ct.columns(); j++)
                {
                    os<<" col="<<j<<" v="<<*(ct.keylist[key]+j);
                    if (j != ct.columns()-1)
                        os<<' ';
                }
                if (key != ct.keylist.size()-1)
                    os<<'\n';
            }
            break;
        }
        case 1:
        {   // index
            HashMultiMap::iterator pos;
            os<<"\nmulti key:row index\n";
            for (pos=ct.keyindexmultimap.begin(); pos!=ct.keyindexmultimap.end(); pos++)
            {
                os<<pos->first<<':'<<pos->second<<'\n';
            }
            // content
            for (size_t key=0; key< ct.keylist.size(); key++)
            {
                os<<"row="<<key;
                for (size_t j=0; j< ct.columns(); j++)
                {
                    os<<" col="<<j<<" v="<<*(ct.keylist[key]+j);
                    if (j != ct.columns()-1)
                        os<<' ';
                }
                if (key != ct.keylist.size()-1)
                    os<<'\n';
            }
            break;
        }
        default:
            break;
        }
    }
    return os;
}
