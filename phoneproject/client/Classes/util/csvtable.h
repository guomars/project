#ifndef __G_CSVTABLE_H__
#define __G_CSVTABLE_H__

#include <string>
#include <map>
#include <vector>
#include <map>
#include "csv.h"

#include "cocos2d.h"

USING_NS_CC;

typedef std::map< int, int > HashMap;

typedef std::map< int, int > HashMultiMap;

void cb1(void* s, size_t len, void* data);

void cb2(int c, void* data);

class csvtable
{
public:
    csvtable();
  
    int Init(const char* filename,
             int   table_type = 0,
             void (*fcb1)(void *, size_t, void *) = cb1,
             void (*fcb2)(int, void *) = cb2);

    bool check_columns(size_t index)  const
    {
        if (index > (columns()-1)) return false;
        return true;
    }

    bool check_rows(size_t index)  const
    {
        if (index > (rows()-1)) return false;
        return true;
    }

    const std::string& getRec(int keyid, const std::string& col_name)
    {
        //  if (table_type != 0)  throw("use wrong function! table_type!=0 ");
        return getRec(keyid, getColIndex(col_name));
    }

    const std::string& getRec(int keyid, int col_index)
    {
        if (table_type != 0)  throw("use wrong function! table_type!=0 ");
        if (check_columns(col_index)==false) throw(std::string("getRec check failed."));
        int ri = getRowIndex(keyid);
        if (check_rows(ri)==false) throw("getRrec check row failed");
        return (*((keylist[ri])+col_index));
    }

    const std::string& getRecFromIndex(int RowIndex, int ColIndex)
    {
		if (check_rows(RowIndex)==false)
			throw(std::string("getRecFromIndex check failed"));
        if (check_columns(ColIndex)==false)
            throw(std::string("getRecFromIndex check failed"));
        return (*(keylist[RowIndex]+ColIndex));
    }

    int getColIndex(const std::string& col_name)
    {
        std::map< std::string, int >::iterator pos;
        pos = titlemap.find(col_name);
        if (pos != titlemap.end())
        {
            return pos->second;
        }
        throw(std::string("getColIndex not found:")+std::string(col_name));
    }

    int getRowIndex(int keyid, int aux_col_index = -1, int aux_keyid = -1)
    {
        if (table_type ==0 && aux_keyid == -1)
        {
            HashMap::iterator pos;
            pos = keyindexmap.find(keyid);
            if (pos != keyindexmap.end())
            {
                return  pos->second;
            }
            throw(std::string("getRowIndex  failed"));
        }
        else if (table_type ==1 && aux_keyid > -1 && aux_col_index > -1)
        {
            std::pair<HashMultiMap::iterator, HashMultiMap::iterator> itpair =
                keyindexmultimap.equal_range(keyid);
            for (; itpair.first != itpair.second; ++itpair.first)
            {
                // itpair.first->second \u4E3Arowindex
                if (aux_keyid ==
                        atoi(getRecFromIndex(itpair.first->second
                                             , aux_col_index).c_str()))
                    return  itpair.first->second;

            }
            throw(std::string("getRowIndex 2 failed"));
        }
        // run here , there must something wrong.
        throw (std::string("table_type and aux_keyid not match or aux_keyid out of range!"));
    }

    int getRowSIndex(int keyid, std::vector<int>& vecIndex)
    {
        vecIndex.clear();
        if (table_type == 0)
        {
            HashMap::iterator pos;
            pos = keyindexmap.find(keyid);
            if (pos != keyindexmap.end())
            {
                vecIndex.push_back(pos->second);
                return 1;
            }
            throw(std::string("getRowIndex  failed"));
            //  return 0;
        }
        else if (table_type == 1)
        {
            std::pair<HashMultiMap::iterator, HashMultiMap::iterator> itpair =
                keyindexmultimap.equal_range(keyid);

            if (itpair.first == itpair.second)
            {
                throw(std::string("getRowIndex 2 failed"));
            }
            for (; itpair.first != itpair.second; ++itpair.first)
            {
                vecIndex.push_back(itpair.first->second);
            }
            return vecIndex.size();
        }
        throw (std::string("table_type and aux_keyid not match or aux_keyid out of range!"));
    }

    int read(const char* zSql=0);
    virtual ~csvtable();
    void fields_count()
    {
        _fields++;
    }
    size_t fields() const
    {
        return _fields;
    }
    void rows_count(int adj=1)
    {
        _rows += adj;
    }
    size_t rows() const
    {
        return _rows;
    }
    void set_columns(size_t c)
    {
        _columns = c;
    }
    size_t columns() const
    {
        return _columns;
    }
    void settitle(bool t)
    {
        _btitle = t;
    }
    bool havetitle() const
    {
        return _btitle;
    }
    friend std::ostream& operator <<(std::ostream&, csvtable&);

    std::map< std::string, int > titlemap;
    std::vector< std::string* > keylist;
    size_t cur_col;

    std::string name() const
    {
        return _filename;
    }

	//==================================================================
	//以下额外提供给lua的接口
	const char * GetRecByColName(int keyid, const char * col_name)
	{
		const char * data = NULL;
		try{
			std::string colname(col_name);
			data = getRec(keyid, colname).c_str();
		}catch(std::string s)
		{
			CCLog("GetRecByColName failed. what=%s",s.c_str());
		}
		return data;
	}
	const char * GetRecByColIndex(int keyid, int col_index)
	{
		const char * data = NULL;
		try{
			data = getRec(keyid, col_index).c_str();
		}catch(std::string s)
		{
			CCLog("GetRecByColIndex failed. what=%s",s.c_str());
		}
		return data;
	}
	const char * GetRecFromIndex(int RowIndex, int ColIndex)
	{
		const char * data = NULL;
		try{
			data = getRecFromIndex(RowIndex, ColIndex).c_str();
		}catch(std::string s)
		{
			CCLog("GetRecFromIndex failed. what=%s",s.c_str());
		}
		return data;
	}
	int GetColIndex(const char * col_name)
	{
		int col = -1;
		try{
			std::string colname(col_name);
			col = getColIndex(colname);
		}catch(std::string s)
		{
			CCLog("GetColIndex failed. what=%s",s.c_str());
		}
		return col;
	}
	int GetRowIndex(int keyid, int aux_col_index = -1, int aux_keyid = -1)
	{
		int row = -1;
		try{
			row = getRowIndex(keyid, aux_col_index , aux_keyid );
		}catch(std::string s)
		{
			CCLog("GetRowIndex failed. what=%s",s.c_str());
		}
		return row;
	}

	int Fields()
	{
		return (int)fields();
	}
	int Rows()
	{
		return (int)rows();
	}
	int Columns()
	{
		return (int)columns();
	}
	//==================================================================
private:
    std::string _filename; 
    int table_type; 
    size_t _fields; 
    size_t _rows; 
    size_t _columns; 
    bool _btitle;

    void (*fcb1)(void*, size_t, void*);
    void (*fcb2)(int, void*);
    struct csv_parser _parser;
    unsigned char _options;

    HashMap keyindexmap;
    HashMultiMap keyindexmultimap;
    int createindex(const char* zSql);
};

#endif
