/*
** Lua binding: MySelf
** Generated automatically by tolua++-1.0.92 on 07/10/14 10:35:47.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_MySelf_open (lua_State* tolua_S);

#include "LuaCocos2d.h"
#include "MyTestClass.h"
#include "DataMgr.h"
#include "NetworkMgr.h"
#include "Configs.h"
#include "CocosGUIUtils.h"
#include "ActionStubs.h"
#include "UIHelper.h"
#include "GFuncMgr.h"
#include "gutil.h"
#include "gamedata.h"
#include "csvtable.h"
#include "MapMgr.h"
#include "AssetsUpdateMgr.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_WidgetName (lua_State* tolua_S)
{
 WidgetName* self = (WidgetName*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UITextArea (lua_State* tolua_S)
{
 UITextArea* self = (UITextArea*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
 CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIWidget (lua_State* tolua_S)
{
 UIWidget* self = (UIWidget*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIInputManager (lua_State* tolua_S)
{
 UIInputManager* self = (UIInputManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_WidgetType (lua_State* tolua_S)
{
 WidgetType* self = (WidgetType*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIRootWidget (lua_State* tolua_S)
{
 UIRootWidget* self = (UIRootWidget*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"UIWidget");
 tolua_usertype(tolua_S,"CCTextAlignment");
 tolua_usertype(tolua_S,"UILayoutUnit");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"UIRootWidget");
 tolua_usertype(tolua_S,"SEL_PushEvent");
 tolua_usertype(tolua_S,"WidgetState");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"SEL_MoveEvent");
 tolua_usertype(tolua_S,"aeditor::AEParamAmmend");
 tolua_usertype(tolua_S,"CCScene");
 tolua_usertype(tolua_S,"UIButton");
 tolua_usertype(tolua_S,"UILayer");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"GMapMgr");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"aStar");
 tolua_usertype(tolua_S,"GFuncMgr");
 tolua_usertype(tolua_S,"AssetsUpdateManager");
 tolua_usertype(tolua_S,"UITextArea");
 tolua_usertype(tolua_S,"update_param");
 tolua_usertype(tolua_S,"download_param");
 tolua_usertype(tolua_S,"aeditor::ActionTemplateTable");
 tolua_usertype(tolua_S,"UILabel");
 tolua_usertype(tolua_S,"CCCallFunc");
 tolua_usertype(tolua_S,"NetworkMgr");
 tolua_usertype(tolua_S,"DataMgr");
 tolua_usertype(tolua_S,"SEL_ReleaseEvent");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"MyTestClass");
 tolua_usertype(tolua_S,"SEL_CancelEvent");
 tolua_usertype(tolua_S,"WidgetType");
 tolua_usertype(tolua_S,"CCAction");
 tolua_usertype(tolua_S,"CCArray");
 tolua_usertype(tolua_S,"CCActionManager");
 tolua_usertype(tolua_S,"UIActionNode");
 tolua_usertype(tolua_S,"ccFontDefinition");
 tolua_usertype(tolua_S,"UIContainerWidget");
 tolua_usertype(tolua_S,"UIInputManager");
 tolua_usertype(tolua_S,"ccBlendFunc");
 tolua_usertype(tolua_S,"CCProgressTimer");
 tolua_usertype(tolua_S,"UIHelper");
 tolua_usertype(tolua_S,"csvtable");
 tolua_usertype(tolua_S,"LabelGravity");
 tolua_usertype(tolua_S,"CCVerticalTextAlignment");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"UIImageView");
 tolua_usertype(tolua_S,"CCSpriteFrame");
 tolua_usertype(tolua_S,"WidgetName");
 tolua_usertype(tolua_S,"CCObject");
}

/* method: new of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_new00
static int tolua_MySelf_UIInputManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIInputManager* tolua_ret = (UIInputManager*)  Mtolua_new((UIInputManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIInputManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_new00_local
static int tolua_MySelf_UIInputManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIInputManager* tolua_ret = (UIInputManager*)  Mtolua_new((UIInputManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIInputManager");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_delete00
static int tolua_MySelf_UIInputManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registWidget of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_registWidget00
static int tolua_MySelf_UIInputManager_registWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registWidget'", NULL);
#endif
  {
   self->registWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: uiSceneHasChanged of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_uiSceneHasChanged00
static int tolua_MySelf_UIInputManager_uiSceneHasChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'uiSceneHasChanged'", NULL);
#endif
  {
   self->uiSceneHasChanged();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'uiSceneHasChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sortWidgets of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_sortWidgets00
static int tolua_MySelf_UIInputManager_sortWidgets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sortWidgets'", NULL);
#endif
  {
   self->sortWidgets(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortWidgets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sortRootWidgets of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_sortRootWidgets00
static int tolua_MySelf_UIInputManager_sortRootWidgets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sortRootWidgets'", NULL);
#endif
  {
   self->sortRootWidgets(root);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortRootWidgets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeManageredWidget of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_removeManageredWidget00
static int tolua_MySelf_UIInputManager_removeManageredWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeManageredWidget'", NULL);
#endif
  {
   self->removeManageredWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeManageredWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkEventWidget of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_checkEventWidget00
static int tolua_MySelf_UIInputManager_checkEventWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkEventWidget'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->checkEventWidget(*touchPoint);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkEventWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addCheckedDoubleClickWidget of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_addCheckedDoubleClickWidget00
static int tolua_MySelf_UIInputManager_addCheckedDoubleClickWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCheckedDoubleClickWidget'", NULL);
#endif
  {
   self->addCheckedDoubleClickWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addCheckedDoubleClickWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_update00
static int tolua_MySelf_UIInputManager_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchBegan of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_onTouchBegan00
static int tolua_MySelf_UIInputManager_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchBegan(touch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchMoved of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_onTouchMoved00
static int tolua_MySelf_UIInputManager_onTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchMoved'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchMoved(touch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchEnd of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_onTouchEnd00
static int tolua_MySelf_UIInputManager_onTouchEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnd'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchEnd(touch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchCancelled of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_onTouchCancelled00
static int tolua_MySelf_UIInputManager_onTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchCancelled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onTouchCancelled(touch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRootWidget of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_setRootWidget00
static int tolua_MySelf_UIInputManager_setRootWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRootWidget'", NULL);
#endif
  {
   self->setRootWidget(root);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRootWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootWidget of class  UIInputManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIInputManager_getRootWidget00
static int tolua_MySelf_UIInputManager_getRootWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIInputManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIInputManager* self = (UIInputManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootWidget'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getRootWidget();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_create00
static int tolua_MySelf_UILayer_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILayer* tolua_ret = (UILayer*)  UILayer::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UILayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_onEnter00
static int tolua_MySelf_UILayer_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnter'", NULL);
#endif
  {
   self->onEnter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onExit of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_onExit00
static int tolua_MySelf_UILayer_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onExit'", NULL);
#endif
  {
   self->onExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnterTransitionDidFinish of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_onEnterTransitionDidFinish00
static int tolua_MySelf_UILayer_onEnterTransitionDidFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnterTransitionDidFinish'", NULL);
#endif
  {
   self->onEnterTransitionDidFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnterTransitionDidFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_ccTouchBegan00
static int tolua_MySelf_UILayer_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(pTouch,pEvent);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_ccTouchMoved00
static int tolua_MySelf_UILayer_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_ccTouchEnded00
static int tolua_MySelf_UILayer_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchCancelled of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_ccTouchCancelled00
static int tolua_MySelf_UILayer_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
  {
   self->ccTouchCancelled(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scheduleUpdate of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_scheduleUpdate00
static int tolua_MySelf_UILayer_scheduleUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scheduleUpdate'", NULL);
#endif
  {
   self->scheduleUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scheduleUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_addWidget00
static int tolua_MySelf_UILayer_addWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addWidget'", NULL);
#endif
  {
   self->addWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeWidgetAndCleanUp of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_removeWidgetAndCleanUp00
static int tolua_MySelf_UILayer_removeWidgetAndCleanUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeWidgetAndCleanUp'", NULL);
#endif
  {
   self->removeWidgetAndCleanUp(widget,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeWidgetAndCleanUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_setVisible00
static int tolua_MySelf_UILayer_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_update00
static int tolua_MySelf_UILayer_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addUpdateEnableWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_addUpdateEnableWidget00
static int tolua_MySelf_UILayer_addUpdateEnableWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addUpdateEnableWidget'", NULL);
#endif
  {
   self->addUpdateEnableWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addUpdateEnableWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeUpdateEnableWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_removeUpdateEnableWidget00
static int tolua_MySelf_UILayer_removeUpdateEnableWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* widget = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeUpdateEnableWidget'", NULL);
#endif
  {
   self->removeUpdateEnableWidget(widget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeUpdateEnableWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetByTag of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_getWidgetByTag00
static int tolua_MySelf_UILayer_getWidgetByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetByTag'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getWidgetByTag(tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetByName of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_getWidgetByName00
static int tolua_MySelf_UILayer_getWidgetByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetByName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getWidgetByName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInputManager of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_getInputManager00
static int tolua_MySelf_UILayer_getInputManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInputManager'", NULL);
#endif
  {
   UIInputManager* tolua_ret = (UIInputManager*)  self->getInputManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIInputManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInputManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_clear00
static int tolua_MySelf_UILayer_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_dispose00
static int tolua_MySelf_UILayer_dispose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRootWidget of class  UILayer */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILayer_getRootWidget00
static int tolua_MySelf_UILayer_getRootWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILayer* self = (UILayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootWidget'", NULL);
#endif
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  self->getRootWidget();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRootWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIRootWidget_new00
static int tolua_MySelf_UIRootWidget_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  Mtolua_new((UIRootWidget)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRootWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIRootWidget_new00_local
static int tolua_MySelf_UIRootWidget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  Mtolua_new((UIRootWidget)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRootWidget");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIRootWidget_delete00
static int tolua_MySelf_UIRootWidget_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIRootWidget* self = (UIRootWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  UIRootWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIRootWidget_create00
static int tolua_MySelf_UIRootWidget_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIRootWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIRootWidget* tolua_ret = (UIRootWidget*)  UIRootWidget::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIRootWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_new00
static int tolua_MySelf_UIWidget_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  Mtolua_new((UIWidget)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_new00_local
static int tolua_MySelf_UIWidget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  Mtolua_new((UIWidget)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_delete00
static int tolua_MySelf_UIWidget_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: releaseResoures of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_releaseResoures00
static int tolua_MySelf_UIWidget_releaseResoures00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'releaseResoures'", NULL);
#endif
  {
   self->releaseResoures();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'releaseResoures'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_create00
static int tolua_MySelf_UIWidget_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIWidget* tolua_ret = (UIWidget*)  UIWidget::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initPressState of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_initPressState00
static int tolua_MySelf_UIWidget_initPressState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"WidgetState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  WidgetState state = *((WidgetState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initPressState'", NULL);
#endif
  {
   self->initPressState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initPressState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPressState of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setPressState00
static int tolua_MySelf_UIWidget_setPressState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"WidgetState",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  WidgetState state = *((WidgetState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPressState'", NULL);
#endif
  {
   self->setPressState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPressState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_addChild00
static int tolua_MySelf_UIWidget_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addChild(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_removeChild00
static int tolua_MySelf_UIWidget_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeChild(child,cleanup);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParentAndCleanup of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_removeFromParentAndCleanup00
static int tolua_MySelf_UIWidget_removeFromParentAndCleanup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromParentAndCleanup'", NULL);
#endif
  {
   self->removeFromParentAndCleanup(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromParentAndCleanup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildrenAndCleanUp of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_removeAllChildrenAndCleanUp00
static int tolua_MySelf_UIWidget_removeAllChildrenAndCleanUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildrenAndCleanUp'", NULL);
#endif
  {
   self->removeAllChildrenAndCleanUp(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildrenAndCleanUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetZOrder of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setWidgetZOrder00
static int tolua_MySelf_UIWidget_setWidgetZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int z = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetZOrder'", NULL);
#endif
  {
   self->setWidgetZOrder(z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetZOrder of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getWidgetZOrder00
static int tolua_MySelf_UIWidget_getWidgetZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetZOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWidgetZOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reorderChild of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_reorderChild00
static int tolua_MySelf_UIWidget_reorderChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* child = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reorderChild'", NULL);
#endif
  {
   self->reorderChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reorderChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setTouchEnable00
static int tolua_MySelf_UIWidget_setTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnable'", NULL);
#endif
  {
   self->setTouchEnable(enable,containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildrenTouchEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateChildrenTouchEnable00
static int tolua_MySelf_UIWidget_updateChildrenTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildrenTouchEnable'", NULL);
#endif
  {
   self->updateChildrenTouchEnable(enable,containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildrenTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isTouchEnable00
static int tolua_MySelf_UIWidget_isTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchEnable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setUpdateEnable00
static int tolua_MySelf_UIWidget_setUpdateEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUpdateEnable'", NULL);
#endif
  {
   self->setUpdateEnable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getUpdateEnable00
static int tolua_MySelf_UIWidget_getUpdateEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateEnable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getUpdateEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFocus of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isFocus00
static int tolua_MySelf_UIWidget_isFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFocus'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFocus();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFocus of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setFocus00
static int tolua_MySelf_UIWidget_setFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool fucos = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFocus'", NULL);
#endif
  {
   self->setFocus(fucos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_disable00
static int tolua_MySelf_UIWidget_disable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disable'", NULL);
#endif
  {
   self->disable(containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: active of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_active00
static int tolua_MySelf_UIWidget_active00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool containChildren = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'active'", NULL);
#endif
  {
   self->active(containChildren);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'active'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildrenActive of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateChildrenActive00
static int tolua_MySelf_UIWidget_updateChildrenActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildrenActive'", NULL);
#endif
  {
   self->updateChildrenActive();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildrenActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildrenDisable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateChildrenDisable00
static int tolua_MySelf_UIWidget_updateChildrenDisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildrenDisable'", NULL);
#endif
  {
   self->updateChildrenDisable();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildrenDisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isActive of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isActive00
static int tolua_MySelf_UIWidget_isActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isActive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isActive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateBeTouchEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateBeTouchEnable00
static int tolua_MySelf_UIWidget_updateBeTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateBeTouchEnable'", NULL);
#endif
  {
   self->updateBeTouchEnable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateBeTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setVisible00
static int tolua_MySelf_UIWidget_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVisible of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isVisible00
static int tolua_MySelf_UIWidget_isVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRect of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRect00
static int tolua_MySelf_UIWidget_getRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRect'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getRect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeRect of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRelativeRect00
static int tolua_MySelf_UIWidget_getRelativeRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeRect'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getRelativeRect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getContentSize00
static int tolua_MySelf_UIWidget_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocationInWindow of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getLocationInWindow00
static int tolua_MySelf_UIWidget_getLocationInWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocationInWindow'", NULL);
#endif
  {
   self->getLocationInWindow();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLocationInWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeLeftPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRelativeLeftPos00
static int tolua_MySelf_UIWidget_getRelativeLeftPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeLeftPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeLeftPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeLeftPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeBottomPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRelativeBottomPos00
static int tolua_MySelf_UIWidget_getRelativeBottomPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeBottomPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeBottomPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeBottomPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeRightPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRelativeRightPos00
static int tolua_MySelf_UIWidget_getRelativeRightPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeRightPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeRightPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeRightPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelativeTopPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRelativeTopPos00
static int tolua_MySelf_UIWidget_getRelativeTopPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelativeTopPos'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRelativeTopPos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeTopPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNode of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getValidNode00
static int tolua_MySelf_UIWidget_getValidNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getValidNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainerNode of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getContainerNode00
static int tolua_MySelf_UIWidget_getContainerNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainerNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getContainerNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContainerNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setWidgetParent00
static int tolua_MySelf_UIWidget_setWidgetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* parent = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetParent'", NULL);
#endif
  {
   self->setWidgetParent(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getWidgetParent00
static int tolua_MySelf_UIWidget_getWidgetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetParent'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getWidgetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getChildByName00
static int tolua_MySelf_UIWidget_getChildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getChildByName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getChildByTag00
static int tolua_MySelf_UIWidget_getChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByTag'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->getChildByTag(tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildren of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getChildren00
static int tolua_MySelf_UIWidget_getChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildren'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getChildren();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPushDownEvent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_addPushDownEvent00
static int tolua_MySelf_UIWidget_addPushDownEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_PushEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_PushEvent selector = *((SEL_PushEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPushDownEvent'", NULL);
#endif
  {
   self->addPushDownEvent(target,selector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPushDownEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addMoveEvent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_addMoveEvent00
static int tolua_MySelf_UIWidget_addMoveEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_MoveEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_MoveEvent selector = *((SEL_MoveEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addMoveEvent'", NULL);
#endif
  {
   self->addMoveEvent(target,selector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMoveEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addReleaseEvent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_addReleaseEvent00
static int tolua_MySelf_UIWidget_addReleaseEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_ReleaseEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_ReleaseEvent selector = *((SEL_ReleaseEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addReleaseEvent'", NULL);
#endif
  {
   self->addReleaseEvent(target,selector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addReleaseEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addCancelEvent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_addCancelEvent00
static int tolua_MySelf_UIWidget_addCancelEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_CancelEvent",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_CancelEvent selector = *((SEL_CancelEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCancelEvent'", NULL);
#endif
  {
   self->addCancelEvent(target,selector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addCancelEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setPosition00
static int tolua_MySelf_UIWidget_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pos = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(*pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setAnchorPoint00
static int tolua_MySelf_UIWidget_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateAnchorPoint of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateAnchorPoint00
static int tolua_MySelf_UIWidget_updateAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateAnchorPoint'", NULL);
#endif
  {
   self->updateAnchorPoint();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getPosition00
static int tolua_MySelf_UIWidget_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchorPoint of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getAnchorPoint00
static int tolua_MySelf_UIWidget_getAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchorPoint'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getAnchorPoint();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setScale00
static int tolua_MySelf_UIWidget_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale'", NULL);
#endif
  {
   self->setScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScale of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getScale00
static int tolua_MySelf_UIWidget_getScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setScaleX00
static int tolua_MySelf_UIWidget_setScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float scaleX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleX'", NULL);
#endif
  {
   self->setScaleX(scaleX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getScaleX00
static int tolua_MySelf_UIWidget_getScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setScaleY00
static int tolua_MySelf_UIWidget_setScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float scaleY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleY'", NULL);
#endif
  {
   self->setScaleY(scaleY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScaleY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getScaleY00
static int tolua_MySelf_UIWidget_getScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScaleY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getScaleY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onScaleDirtyChanged of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onScaleDirtyChanged00
static int tolua_MySelf_UIWidget_onScaleDirtyChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onScaleDirtyChanged'", NULL);
#endif
  {
   self->onScaleDirtyChanged();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onScaleDirtyChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onScaleXDirtyChanged of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onScaleXDirtyChanged00
static int tolua_MySelf_UIWidget_onScaleXDirtyChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onScaleXDirtyChanged'", NULL);
#endif
  {
   self->onScaleXDirtyChanged();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onScaleXDirtyChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onScaleYDirtyChanged of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onScaleYDirtyChanged00
static int tolua_MySelf_UIWidget_onScaleYDirtyChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onScaleYDirtyChanged'", NULL);
#endif
  {
   self->onScaleYDirtyChanged();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onScaleYDirtyChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setRotation00
static int tolua_MySelf_UIWidget_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float rotation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'", NULL);
#endif
  {
   self->setRotation(rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRotation00
static int tolua_MySelf_UIWidget_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setRotationX00
static int tolua_MySelf_UIWidget_setRotationX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float rotationX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationX'", NULL);
#endif
  {
   self->setRotationX(rotationX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotationX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRotationX00
static int tolua_MySelf_UIWidget_getRotationX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotationX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotationX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotationX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotationY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setRotationY00
static int tolua_MySelf_UIWidget_setRotationY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float rotationY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotationY'", NULL);
#endif
  {
   self->setRotationY(rotationY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotationY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotationY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getRotationY00
static int tolua_MySelf_UIWidget_getRotationY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotationY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotationY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotationY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSkewX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setSkewX00
static int tolua_MySelf_UIWidget_setSkewX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float skewX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSkewX'", NULL);
#endif
  {
   self->setSkewX(skewX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSkewX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkewX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getSkewX00
static int tolua_MySelf_UIWidget_getSkewX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkewX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSkewX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkewX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSkewY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setSkewY00
static int tolua_MySelf_UIWidget_setSkewY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float skewY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSkewY'", NULL);
#endif
  {
   self->setSkewY(skewY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSkewY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSkewY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getSkewY00
static int tolua_MySelf_UIWidget_getSkewY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSkewY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSkewY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSkewY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setFlipX00
static int tolua_MySelf_UIWidget_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isFlipX00
static int tolua_MySelf_UIWidget_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setFlipY00
static int tolua_MySelf_UIWidget_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isFlipY00
static int tolua_MySelf_UIWidget_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setColor00
static int tolua_MySelf_UIWidget_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getColor00
static int tolua_MySelf_UIWidget_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setOpacity00
static int tolua_MySelf_UIWidget_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int opacity = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getOpacity00
static int tolua_MySelf_UIWidget_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeOpacityEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isCascadeOpacityEnabled00
static int tolua_MySelf_UIWidget_isCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeOpacityEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeOpacityEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeOpacityEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setCascadeOpacityEnabled00
static int tolua_MySelf_UIWidget_setCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeOpacityEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeOpacityEnabled'", NULL);
#endif
  {
   self->setCascadeOpacityEnabled(cascadeOpacityEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeColorEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isCascadeColorEnabled00
static int tolua_MySelf_UIWidget_isCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeColorEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeColorEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeColorEnabled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setCascadeColorEnabled00
static int tolua_MySelf_UIWidget_setCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeColorEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeColorEnabled'", NULL);
#endif
  {
   self->setCascadeColorEnabled(cascadeColorEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setBlendFunc00
static int tolua_MySelf_UIWidget_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc blendFunc = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(blendFunc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionManager of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setActionManager00
static int tolua_MySelf_UIWidget_setActionManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCActionManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCActionManager* actionManager = ((CCActionManager*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionManager'", NULL);
#endif
  {
   self->setActionManager(actionManager);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionManager of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getActionManager00
static int tolua_MySelf_UIWidget_getActionManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionManager'", NULL);
#endif
  {
   CCActionManager* tolua_ret = (CCActionManager*)  self->getActionManager();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCActionManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAction of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_runAction00
static int tolua_MySelf_UIWidget_runAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCAction* action = ((CCAction*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAction'", NULL);
#endif
  {
   CCAction* tolua_ret = (CCAction*)  self->runAction(action);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'runAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAllActions of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_stopAllActions00
static int tolua_MySelf_UIWidget_stopAllActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAllActions'", NULL);
#endif
  {
   self->stopAllActions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAllActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAction of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_stopAction00
static int tolua_MySelf_UIWidget_stopAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  CCAction* action = ((CCAction*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAction'", NULL);
#endif
  {
   self->stopAction(action);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopActionByTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_stopActionByTag00
static int tolua_MySelf_UIWidget_stopActionByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopActionByTag'", NULL);
#endif
  {
   self->stopActionByTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopActionByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionByTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getActionByTag00
static int tolua_MySelf_UIWidget_getActionByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionByTag'", NULL);
#endif
  {
   CCAction* tolua_ret = (CCAction*)  self->getActionByTag(tag);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setActionTag00
static int tolua_MySelf_UIWidget_setActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionTag'", NULL);
#endif
  {
   self->setActionTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getActionTag00
static int tolua_MySelf_UIWidget_getActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getActionTag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNeedCheckVisibleDepandParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setNeedCheckVisibleDepandParent00
static int tolua_MySelf_UIWidget_setNeedCheckVisibleDepandParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool need = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNeedCheckVisibleDepandParent'", NULL);
#endif
  {
   self->setNeedCheckVisibleDepandParent(need);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNeedCheckVisibleDepandParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: didNotSelectSelf of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_didNotSelectSelf00
static int tolua_MySelf_UIWidget_didNotSelectSelf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'didNotSelectSelf'", NULL);
#endif
  {
   self->didNotSelectSelf();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'didNotSelectSelf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchBegan of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onTouchBegan00
static int tolua_MySelf_UIWidget_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   self->onTouchBegan(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchMoved of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onTouchMoved00
static int tolua_MySelf_UIWidget_onTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchMoved'", NULL);
#endif
  {
   self->onTouchMoved(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchEnded of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onTouchEnded00
static int tolua_MySelf_UIWidget_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchCancelled of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onTouchCancelled00
static int tolua_MySelf_UIWidget_onTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchCancelled'", NULL);
#endif
  {
   self->onTouchCancelled(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchLongClicked of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_onTouchLongClicked00
static int tolua_MySelf_UIWidget_onTouchLongClicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchLongClicked'", NULL);
#endif
  {
   self->onTouchLongClicked(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchLongClicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isClippingEnable of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_isClippingEnable00
static int tolua_MySelf_UIWidget_isClippingEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isClippingEnable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isClippingEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isClippingEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_update00
static int tolua_MySelf_UIWidget_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAtSelfBody of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_pointAtSelfBody00
static int tolua_MySelf_UIWidget_pointAtSelfBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pointAtSelfBody'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->pointAtSelfBody(*pt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAtSelfBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkVisibleDependParent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_checkVisibleDependParent00
static int tolua_MySelf_UIWidget_checkVisibleDependParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkVisibleDependParent'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkVisibleDependParent(*pt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkVisibleDependParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkChildInfo of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_checkChildInfo00
static int tolua_MySelf_UIWidget_checkChildInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int handleState = ((int)  tolua_tonumber(tolua_S,2,0));
  UIWidget* sender = ((UIWidget*)  tolua_tousertype(tolua_S,3,0));
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkChildInfo'", NULL);
#endif
  {
   self->checkChildInfo(handleState,sender,*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkChildInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAbsoluteScaleX of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getAbsoluteScaleX00
static int tolua_MySelf_UIWidget_getAbsoluteScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAbsoluteScaleX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAbsoluteScaleX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAbsoluteScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAbsoluteScaleY of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getAbsoluteScaleY00
static int tolua_MySelf_UIWidget_getAbsoluteScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAbsoluteScaleY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAbsoluteScaleY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAbsoluteScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAbsoluteVisible of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getAbsoluteVisible00
static int tolua_MySelf_UIWidget_getAbsoluteVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAbsoluteVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getAbsoluteVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAbsoluteVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildrenVisibleDirty of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateChildrenVisibleDirty00
static int tolua_MySelf_UIWidget_updateChildrenVisibleDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool dirty = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildrenVisibleDirty'", NULL);
#endif
  {
   self->updateChildrenVisibleDirty(dirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildrenVisibleDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildrenOpacityDirty of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateChildrenOpacityDirty00
static int tolua_MySelf_UIWidget_updateChildrenOpacityDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool dirty = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildrenOpacityDirty'", NULL);
#endif
  {
   self->updateChildrenOpacityDirty(dirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildrenOpacityDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: adaptSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_adaptSize00
static int tolua_MySelf_UIWidget_adaptSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  float xProportion = ((float)  tolua_tonumber(tolua_S,2,0));
  float yProportion = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'adaptSize'", NULL);
#endif
  {
   self->adaptSize(xProportion,yProportion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'adaptSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCreateFromFile of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setCreateFromFile00
static int tolua_MySelf_UIWidget_setCreateFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  bool is = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCreateFromFile'", NULL);
#endif
  {
   self->setCreateFromFile(is);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCreateFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFileDesignSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setFileDesignSize00
static int tolua_MySelf_UIWidget_setFileDesignSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFileDesignSize'", NULL);
#endif
  {
   self->setFileDesignSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFileDesignSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDesignSize of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getFileDesignSize00
static int tolua_MySelf_UIWidget_getFileDesignSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDesignSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getFileDesignSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDesignSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUILayer of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setUILayer00
static int tolua_MySelf_UIWidget_setUILayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UILayer* uiLayer = ((UILayer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUILayer'", NULL);
#endif
  {
   self->setUILayer(uiLayer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUILayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildrenUILayer of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_updateChildrenUILayer00
static int tolua_MySelf_UIWidget_updateChildrenUILayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UILayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UILayer* uiLayer = ((UILayer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildrenUILayer'", NULL);
#endif
  {
   self->updateChildrenUILayer(uiLayer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildrenUILayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: structureChangedEvent of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_structureChangedEvent00
static int tolua_MySelf_UIWidget_structureChangedEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'structureChangedEvent'", NULL);
#endif
  {
   self->structureChangedEvent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'structureChangedEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: disableUpdate of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_disableUpdate00
static int tolua_MySelf_UIWidget_disableUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disableUpdate'", NULL);
#endif
  {
   self->disableUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disableUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchStartPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getTouchStartPos00
static int tolua_MySelf_UIWidget_getTouchStartPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchStartPos'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getTouchStartPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchStartPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchMovePos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getTouchMovePos00
static int tolua_MySelf_UIWidget_getTouchMovePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchMovePos'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getTouchMovePos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchMovePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchEndPos of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getTouchEndPos00
static int tolua_MySelf_UIWidget_getTouchEndPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchEndPos'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getTouchEndPos();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchEndPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidgetTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setWidgetTag00
static int tolua_MySelf_UIWidget_setWidgetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidgetTag'", NULL);
#endif
  {
   self->setWidgetTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidgetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetTag of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getWidgetTag00
static int tolua_MySelf_UIWidget_getWidgetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWidgetTag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setName00
static int tolua_MySelf_UIWidget_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getName00
static int tolua_MySelf_UIWidget_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetType of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getWidgetType00
static int tolua_MySelf_UIWidget_getWidgetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetType'", NULL);
#endif
  {
   WidgetType tolua_ret = (WidgetType)  self->getWidgetType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((WidgetType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"WidgetType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(WidgetType));
     tolua_pushusertype(tolua_S,tolua_obj,"WidgetType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidgetName of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_getWidgetName00
static int tolua_MySelf_UIWidget_getWidgetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidgetName'", NULL);
#endif
  {
   WidgetName tolua_ret = (WidgetName)  self->getWidgetName();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((WidgetName)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"WidgetName");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(WidgetName));
     tolua_pushusertype(tolua_S,tolua_obj,"WidgetName");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidgetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBindingAction of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIWidget_setBindingAction00
static int tolua_MySelf_UIWidget_setBindingAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIActionNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
  UIActionNode* actionNode = ((UIActionNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBindingAction'", NULL);
#endif
  {
   self->setBindingAction(actionNode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBindingAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __UILayoutUnit__ of class  UIWidget */
#ifndef TOLUA_DISABLE_tolua_get_UIWidget___UILayoutUnit__
static int tolua_get_UIWidget___UILayoutUnit__(lua_State* tolua_S)
{
  UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__UILayoutUnit__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<UILayoutUnit*>(self), "UILayoutUnit");
#else
   tolua_pushusertype(tolua_S,(void*)((UILayoutUnit*)self), "UILayoutUnit");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWidgetFromJsonFile of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_createWidgetFromJsonFile00
static int tolua_MySelf_UIHelper_createWidgetFromJsonFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createWidgetFromJsonFile'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->createWidgetFromJsonFile(fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWidgetFromJsonFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_instance00
static int tolua_MySelf_UIHelper_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIHelper* tolua_ret = (UIHelper*)  UIHelper::instance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIHelper");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeUIHelper of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_purgeUIHelper00
static int tolua_MySelf_UIHelper_purgeUIHelper00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIHelper::purgeUIHelper();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeUIHelper'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSpriteFrame of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_addSpriteFrame00
static int tolua_MySelf_UIHelper_addSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSpriteFrame'", NULL);
#endif
  {
   self->addSpriteFrame(fileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSpriteFrame of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_removeSpriteFrame00
static int tolua_MySelf_UIHelper_removeSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSpriteFrame'", NULL);
#endif
  {
   self->removeSpriteFrame(fileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllSpriteFrame of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_removeAllSpriteFrame00
static int tolua_MySelf_UIHelper_removeAllSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllSpriteFrame'", NULL);
#endif
  {
   self->removeAllSpriteFrame();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByTag of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_seekWidgetByTag00
static int tolua_MySelf_UIHelper_seekWidgetByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seekWidgetByTag'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->seekWidgetByTag(root,tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByName of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_seekWidgetByName00
static int tolua_MySelf_UIHelper_seekWidgetByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seekWidgetByName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->seekWidgetByName(root,name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekActionWidgetByActionTag of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_seekActionWidgetByActionTag00
static int tolua_MySelf_UIHelper_seekActionWidgetByActionTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seekActionWidgetByActionTag'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->seekActionWidgetByActionTag(root,tag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekActionWidgetByActionTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: seekWidgetByRelativeName of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_seekWidgetByRelativeName00
static int tolua_MySelf_UIHelper_seekWidgetByRelativeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  UIWidget* root = ((UIWidget*)  tolua_tousertype(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seekWidgetByRelativeName'", NULL);
#endif
  {
   UIWidget* tolua_ret = (UIWidget*)  self->seekWidgetByRelativeName(root,name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seekWidgetByRelativeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFileDesignWidth of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_setFileDesignWidth00
static int tolua_MySelf_UIHelper_setFileDesignWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFileDesignWidth'", NULL);
#endif
  {
   self->setFileDesignWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFileDesignWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDesignWidth of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_getFileDesignWidth00
static int tolua_MySelf_UIHelper_getFileDesignWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDesignWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFileDesignWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDesignWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFileDesignHeight of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_setFileDesignHeight00
static int tolua_MySelf_UIHelper_setFileDesignHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFileDesignHeight'", NULL);
#endif
  {
   self->setFileDesignHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFileDesignHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileDesignHeight of class  UIHelper */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIHelper_getFileDesignHeight00
static int tolua_MySelf_UIHelper_getFileDesignHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIHelper* self = (UIHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileDesignHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFileDesignHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileDesignHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_create00
static int tolua_MySelf_UIImageView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIImageView* tolua_ret = (UIImageView*)  UIImageView::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIImageView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTexture of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setTexture00
static int tolua_MySelf_UIImageView_setTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  TextureResType texType = ((TextureResType) (int)  tolua_tonumber(tolua_S,3,UI_TEX_TYPE_LOCAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTexture'", NULL);
#endif
  {
   self->setTexture(fileName,texType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextureRect of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setTextureRect00
static int tolua_MySelf_UIImageView_setTextureRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextureRect'", NULL);
#endif
  {
   self->setTextureRect(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextureRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doubleClickEvent of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_doubleClickEvent00
static int tolua_MySelf_UIImageView_doubleClickEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doubleClickEvent'", NULL);
#endif
  {
   self->doubleClickEvent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doubleClickEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkDoubleClick of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_checkDoubleClick00
static int tolua_MySelf_UIImageView_checkDoubleClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkDoubleClick'", NULL);
#endif
  {
   self->checkDoubleClick(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkDoubleClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDoubleClickEnable of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setDoubleClickEnable00
static int tolua_MySelf_UIImageView_setDoubleClickEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDoubleClickEnable'", NULL);
#endif
  {
   self->setDoubleClickEnable(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDoubleClickEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setFlipX00
static int tolua_MySelf_UIImageView_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setFlipY00
static int tolua_MySelf_UIImageView_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_isFlipX00
static int tolua_MySelf_UIImageView_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_isFlipY00
static int tolua_MySelf_UIImageView_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Enable of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setScale9Enable00
static int tolua_MySelf_UIImageView_setScale9Enable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Enable'", NULL);
#endif
  {
   self->setScale9Enable(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Enable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale9Size of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setScale9Size00
static int tolua_MySelf_UIImageView_setScale9Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale9Size'", NULL);
#endif
  {
   self->setScale9Size(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale9Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplayFrame of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setDisplayFrame00
static int tolua_MySelf_UIImageView_setDisplayFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* pNewFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplayFrame'", NULL);
#endif
  {
   self->setDisplayFrame(pNewFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplayFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpriteFrame of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setSpriteFrame00
static int tolua_MySelf_UIImageView_setSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* pNewFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpriteFrame'", NULL);
#endif
  {
   self->setSpriteFrame(pNewFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPreferredSize of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setPreferredSize00
static int tolua_MySelf_UIImageView_setPreferredSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* pSize = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPreferredSize'", NULL);
#endif
  {
   self->setPreferredSize(*pSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPreferredSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetLeft of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setInsetLeft00
static int tolua_MySelf_UIImageView_setInsetLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  float insetLeft = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetLeft'", NULL);
#endif
  {
   self->setInsetLeft(insetLeft);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetTop of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setInsetTop00
static int tolua_MySelf_UIImageView_setInsetTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  float insetTop = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetTop'", NULL);
#endif
  {
   self->setInsetTop(insetTop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetRight of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setInsetRight00
static int tolua_MySelf_UIImageView_setInsetRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  float insetRight = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetRight'", NULL);
#endif
  {
   self->setInsetRight(insetRight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInsetBottom of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setInsetBottom00
static int tolua_MySelf_UIImageView_setInsetBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  float insetBottom = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInsetBottom'", NULL);
#endif
  {
   self->setInsetBottom(insetBottom);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInsetBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCapInsets of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setCapInsets00
static int tolua_MySelf_UIImageView_setCapInsets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCRect* capInsets = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCapInsets'", NULL);
#endif
  {
   self->setCapInsets(*capInsets);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCapInsets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNode of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_getValidNode00
static int tolua_MySelf_UIImageView_getValidNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getValidNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_setAnchorPoint00
static int tolua_MySelf_UIImageView_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchBegan of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_onTouchBegan00
static int tolua_MySelf_UIImageView_onTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchBegan'", NULL);
#endif
  {
   self->onTouchBegan(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTouchEnded of class  UIImageView */
#ifndef TOLUA_DISABLE_tolua_MySelf_UIImageView_onTouchEnded00
static int tolua_MySelf_UIImageView_onTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIImageView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIImageView* self = (UIImageView*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* touchPoint = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTouchEnded'", NULL);
#endif
  {
   self->onTouchEnded(*touchPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_new00
static int tolua_MySelf_UITextArea_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITextArea* tolua_ret = (UITextArea*)  Mtolua_new((UITextArea)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UITextArea");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_new00_local
static int tolua_MySelf_UITextArea_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITextArea* tolua_ret = (UITextArea*)  Mtolua_new((UITextArea)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UITextArea");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_create00
static int tolua_MySelf_UITextArea_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITextArea* tolua_ret = (UITextArea*)  UITextArea::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UITextArea");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initNodes of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_initNodes00
static int tolua_MySelf_UITextArea_initNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initNodes'", NULL);
#endif
  {
   self->initNodes();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setText00
static int tolua_MySelf_UITextArea_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextAreaSize of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setTextAreaSize00
static int tolua_MySelf_UITextArea_setTextAreaSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextAreaSize'", NULL);
#endif
  {
   self->setTextAreaSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextAreaSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextHorizontalAlignment of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setTextHorizontalAlignment00
static int tolua_MySelf_UITextArea_setTextHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCTextAlignment",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  CCTextAlignment alignment = *((CCTextAlignment*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextHorizontalAlignment'", NULL);
#endif
  {
   self->setTextHorizontalAlignment(alignment);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextVerticalAlignment of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setTextVerticalAlignment00
static int tolua_MySelf_UITextArea_setTextVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCVerticalTextAlignment",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  CCVerticalTextAlignment alignment = *((CCVerticalTextAlignment*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextVerticalAlignment'", NULL);
#endif
  {
   self->setTextVerticalAlignment(alignment);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringLength of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_getStringLength00
static int tolua_MySelf_UITextArea_getStringLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getStringLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_getStringValue00
static int tolua_MySelf_UITextArea_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringValue'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStringValue();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextColor of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setTextColor00
static int tolua_MySelf_UITextArea_setTextColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  int r = ((int)  tolua_tonumber(tolua_S,2,0));
  int g = ((int)  tolua_tonumber(tolua_S,3,0));
  int b = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextColor'", NULL);
#endif
  {
   self->setTextColor(r,g,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontSize of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setFontSize00
static int tolua_MySelf_UITextArea_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontSize'", NULL);
#endif
  {
   self->setFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setFontName00
static int tolua_MySelf_UITextArea_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(fontName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setFlipX00
static int tolua_MySelf_UITextArea_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setFlipY00
static int tolua_MySelf_UITextArea_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_isFlipX00
static int tolua_MySelf_UITextArea_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_isFlipY00
static int tolua_MySelf_UITextArea_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNode of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_getValidNode00
static int tolua_MySelf_UITextArea_getValidNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getValidNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UITextArea */
#ifndef TOLUA_DISABLE_tolua_MySelf_UITextArea_setAnchorPoint00
static int tolua_MySelf_UITextArea_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITextArea",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITextArea* self = (UITextArea*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_create00
static int tolua_MySelf_UILabel_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UILabel* tolua_ret = (UILabel*)  UILabel::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UILabel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setText00
static int tolua_MySelf_UILabel_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextDefinition of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setTextDefinition00
static int tolua_MySelf_UILabel_setTextDefinition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ccFontDefinition",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  ccFontDefinition* theDefinition = ((ccFontDefinition*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextDefinition'", NULL);
#endif
  {
   self->setTextDefinition(theDefinition);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextDefinition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringValue of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_getStringValue00
static int tolua_MySelf_UILabel_getStringValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringValue'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStringValue();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringLength of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_getStringLength00
static int tolua_MySelf_UILabel_getStringLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getStringLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStringLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontSize of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setFontSize00
static int tolua_MySelf_UILabel_setFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontSize'", NULL);
#endif
  {
   self->setFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontName of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setFontName00
static int tolua_MySelf_UILabel_setFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontName'", NULL);
#endif
  {
   self->setFontName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFontName of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_getFontName00
static int tolua_MySelf_UILabel_getFontName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  std::string strFontName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFontName'", NULL);
#endif
  {
   self->getFontName(strFontName);
   tolua_pushcppstring(tolua_S,(const char*)strFontName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFontName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchScaleChangeAble of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setTouchScaleChangeAble00
static int tolua_MySelf_UILabel_setTouchScaleChangeAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool able = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchScaleChangeAble'", NULL);
#endif
  {
   self->setTouchScaleChangeAble(able);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchScaleChangeAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchScaleChangeAble of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_getTouchScaleChangeAble00
static int tolua_MySelf_UILabel_getTouchScaleChangeAble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchScaleChangeAble'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getTouchScaleChangeAble();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchScaleChangeAble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clickScale of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_clickScale00
static int tolua_MySelf_UILabel_clickScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clickScale'", NULL);
#endif
  {
   self->clickScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clickScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipX of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setFlipX00
static int tolua_MySelf_UILabel_setFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool flipX = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipX'", NULL);
#endif
  {
   self->setFlipX(flipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFlipY of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setFlipY00
static int tolua_MySelf_UILabel_setFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  bool flipY = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFlipY'", NULL);
#endif
  {
   self->setFlipY(flipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipX of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_isFlipX00
static int tolua_MySelf_UILabel_isFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipX'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipX();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFlipY of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_isFlipY00
static int tolua_MySelf_UILabel_isFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFlipY'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFlipY();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGravity of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setGravity00
static int tolua_MySelf_UILabel_setGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LabelGravity",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  LabelGravity gravity = *((LabelGravity*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGravity'", NULL);
#endif
  {
   self->setGravity(gravity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: adaptSize of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_adaptSize00
static int tolua_MySelf_UILabel_adaptSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  float xProportion = ((float)  tolua_tonumber(tolua_S,2,0));
  float yProportion = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'adaptSize'", NULL);
#endif
  {
   self->adaptSize(xProportion,yProportion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'adaptSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValidNode of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_getValidNode00
static int tolua_MySelf_UILabel_getValidNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValidNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getValidNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValidNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchorPoint of class  UILabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_UILabel_setAnchorPoint00
static int tolua_MySelf_UILabel_setAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UILabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UILabel* self = (UILabel*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchorPoint'", NULL);
#endif
  {
   self->setAnchorPoint(*pt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_PATH */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_PATH00
static int tolua_MySelf_GET_PATH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* strPath = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* strFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  GET_PATH(strPath,strFileName);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_PATH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_PATH2 */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_PATH200
static int tolua_MySelf_GET_PATH200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* strPath = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* strFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  GET_PATH2(strPath,strFileName);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_PATH2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: STRING_WITH_INT */
#ifndef TOLUA_DISABLE_tolua_MySelf_STRING_WITH_INT00
static int tolua_MySelf_STRING_WITH_INT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  int t = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  STRING_WITH_INT(str,t);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'STRING_WITH_INT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: STRING_WITH_INT2 */
#ifndef TOLUA_DISABLE_tolua_MySelf_STRING_WITH_INT200
static int tolua_MySelf_STRING_WITH_INT200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  int t = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  STRING_WITH_INT2(str,t);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'STRING_WITH_INT2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_WIN_SIZE */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_WIN_SIZE00
static int tolua_MySelf_GET_WIN_SIZE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const CCSize& tolua_ret = (const CCSize&)  GET_WIN_SIZE();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_WIN_SIZE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_POS_CENTOR */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_POS_CENTOR00
static int tolua_MySelf_GET_POS_CENTOR00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const CCPoint& tolua_ret = (const CCPoint&)  GET_POS_CENTOR();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_POS_CENTOR'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_CCOBJECT_DISTANCE */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_CCOBJECT_DISTANCE00
static int tolua_MySelf_GET_CCOBJECT_DISTANCE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* obj1 = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  CCNode* obj2 = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   const float tolua_ret = (const float)  GET_CCOBJECT_DISTANCE(obj1,obj2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_CCOBJECT_DISTANCE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_CCP_DISTANCE */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_CCP_DISTANCE00
static int tolua_MySelf_GET_CCP_DISTANCE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCPoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCPoint* p1 = ((const CCPoint*)  tolua_tousertype(tolua_S,1,0));
  const CCPoint* p2 = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   const float tolua_ret = (const float)  GET_CCP_DISTANCE(p1,p2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_CCP_DISTANCE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GET_CCP_ANGLE */
#ifndef TOLUA_DISABLE_tolua_MySelf_GET_CCP_ANGLE00
static int tolua_MySelf_GET_CCP_ANGLE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCPoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCPoint* p1 = ((const CCPoint*)  tolua_tousertype(tolua_S,1,0));
  const CCPoint* p2 = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   const float tolua_ret = (const float)  GET_CCP_ANGLE(p1,p2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET_CCP_ANGLE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RADIANS_TO_DEGREES */
#ifndef TOLUA_DISABLE_tolua_MySelf_RADIANS_TO_DEGREES00
static int tolua_MySelf_RADIANS_TO_DEGREES00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float radius = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   const float tolua_ret = (const float)  RADIANS_TO_DEGREES(radius);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RADIANS_TO_DEGREES'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DEGREES_TO_RADIANS */
#ifndef TOLUA_DISABLE_tolua_MySelf_DEGREES_TO_RADIANS00
static int tolua_MySelf_DEGREES_TO_RADIANS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float degrees = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   const float tolua_ret = (const float)  DEGREES_TO_RADIANS(degrees);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DEGREES_TO_RADIANS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SET_NODE_ZORDER */
#ifndef TOLUA_DISABLE_tolua_MySelf_SET_NODE_ZORDER00
static int tolua_MySelf_SET_NODE_ZORDER00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  int zorder = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   SET_NODE_ZORDER(node,zorder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SET_NODE_ZORDER'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: POINT_INT_NODE */
#ifndef TOLUA_DISABLE_tolua_MySelf_POINT_INT_NODE00
static int tolua_MySelf_POINT_INT_NODE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const CCPoint* pt = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  POINT_INT_NODE(node,*pt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'POINT_INT_NODE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SET_SPRITE_TEXTURE */
#ifndef TOLUA_DISABLE_tolua_MySelf_SET_SPRITE_TEXTURE00
static int tolua_MySelf_SET_SPRITE_TEXTURE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSprite* node = ((CCSprite*)  tolua_tousertype(tolua_S,1,0));
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   SET_SPRITE_TEXTURE(node,fileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SET_SPRITE_TEXTURE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CreateStrideLabelContainer */
#ifndef TOLUA_DISABLE_tolua_MySelf_CreateStrideLabelContainer00
static int tolua_MySelf_CreateStrideLabelContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* szText = ((const char*)  tolua_tostring(tolua_S,1,0));
  int fontSize = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  CreateStrideLabelContainer(szText,fontSize);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateStrideLabelContainer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CreateStrideLabelContainer */
#ifndef TOLUA_DISABLE_tolua_MySelf_CreateStrideLabelContainer01
static int tolua_MySelf_CreateStrideLabelContainer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* szText = ((const char*)  tolua_tostring(tolua_S,1,0));
  int fontSize = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  CreateStrideLabelContainer(szText,fontSize,*color);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MySelf_CreateStrideLabelContainer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: CreateStrideLabelContainer */
#ifndef TOLUA_DISABLE_tolua_MySelf_CreateStrideLabelContainer02
static int tolua_MySelf_CreateStrideLabelContainer02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* szText = ((const char*)  tolua_tostring(tolua_S,1,0));
  int fontSize = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  const ccColor3B* strideColor = ((const ccColor3B*)  tolua_tousertype(tolua_S,4,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  CreateStrideLabelContainer(szText,fontSize,*color,*strideColor);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MySelf_CreateStrideLabelContainer01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: CreateStrideLabelContainer */
#ifndef TOLUA_DISABLE_tolua_MySelf_CreateStrideLabelContainer03
static int tolua_MySelf_CreateStrideLabelContainer03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const ccColor3B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* szText = ((const char*)  tolua_tostring(tolua_S,1,0));
  int fontSize = ((int)  tolua_tonumber(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  const ccColor3B* strideColor = ((const ccColor3B*)  tolua_tousertype(tolua_S,4,0));
  const CCPoint* anchor = ((const CCPoint*)  tolua_tousertype(tolua_S,5,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  CreateStrideLabelContainer(szText,fontSize,*color,*strideColor,*anchor);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_MySelf_CreateStrideLabelContainer02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetMultiColorLabelText */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetMultiColorLabelText00
static int tolua_MySelf_SetMultiColorLabelText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* szText = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   SetMultiColorLabelText(pRoot,szLabelName,szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMultiColorLabelText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetWidgetAnchorPoint */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetWidgetAnchorPoint00
static int tolua_MySelf_SetWidgetAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCPoint vAnchorPoint = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   SetWidgetAnchorPoint(pRoot,szName,vAnchorPoint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidgetAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetLabelColor */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetLabelColor00
static int tolua_MySelf_SetLabelColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  {
   SetLabelColor(pRoot,szLabelName,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetTextAreaText */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetTextAreaText00
static int tolua_MySelf_SetTextAreaText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* szText = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   SetTextAreaText(pRoot,szName,szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextAreaText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetLabelText */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetLabelText00
static int tolua_MySelf_SetLabelText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* szText = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   SetLabelText(pRoot,szLabelName,szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetLabelTextWithInt */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetLabelTextWithInt00
static int tolua_MySelf_SetLabelTextWithInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nNumber = ((int)  tolua_tonumber(tolua_S,3,0));
  bool bAnim = ((bool)  tolua_toboolean(tolua_S,4,true));
  {
   SetLabelTextWithInt(pRoot,szLabelName,nNumber,bAnim);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelTextWithInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetLabelTextWithIntSign */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetLabelTextWithIntSign00
static int tolua_MySelf_SetLabelTextWithIntSign00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nNumber = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   SetLabelTextWithIntSign(pRoot,szLabelName,nNumber);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelTextWithIntSign'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetLabelValue */
#ifndef TOLUA_DISABLE_tolua_MySelf_GetLabelValue00
static int tolua_MySelf_GetLabelValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   int tolua_ret = (int)  GetLabelValue(pRoot,szLabelName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLabelValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetLabelAtlasText */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetLabelAtlasText00
static int tolua_MySelf_SetLabelAtlasText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* szText = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   SetLabelAtlasText(pRoot,szLabelName,szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelAtlasText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetLabelAtlasTextWithInt */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetLabelAtlasTextWithInt00
static int tolua_MySelf_SetLabelAtlasTextWithInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nNumber = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   SetLabelAtlasTextWithInt(pRoot,szLabelName,nNumber);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelAtlasTextWithInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetProgressBarPercent */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetProgressBarPercent00
static int tolua_MySelf_SetProgressBarPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szPBName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nPercent = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   SetProgressBarPercent(pRoot,szPBName,nPercent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProgressBarPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: HideWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_HideWidget00
static int tolua_MySelf_HideWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   HideWidget(pRoot,szName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HideWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ShowWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_ShowWidget00
static int tolua_MySelf_ShowWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   ShowWidget(pRoot,szName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetTabHighlight */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetTabHighlight00
static int tolua_MySelf_SetTabHighlight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szTabBtn = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* szHighlightPic = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   SetTabHighlight(pRoot,szTabBtn,szHighlightPic);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTabHighlight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetWidgetTag */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetWidgetTag00
static int tolua_MySelf_SetWidgetTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   SetWidgetTag(pRoot,szName,tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidgetTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: EnableWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_EnableWidget00
static int tolua_MySelf_EnableWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   EnableWidget(pRoot,szName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DisableWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_DisableWidget00
static int tolua_MySelf_DisableWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   DisableWidget(pRoot,szName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisableWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetWidgetPosition */
#ifndef TOLUA_DISABLE_tolua_MySelf_GetWidgetPosition00
static int tolua_MySelf_GetWidgetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCPoint tolua_ret = (CCPoint)  GetWidgetPosition(pRoot,szName);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidgetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AddEffectToWidget */
#ifndef TOLUA_DISABLE_tolua_MySelf_AddEffectToWidget00
static int tolua_MySelf_AddEffectToWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szWidgetName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* szEffectName = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   AddEffectToWidget(pRoot,szWidgetName,szEffectName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddEffectToWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AddDynamicDigitLabel */
#ifndef TOLUA_DISABLE_tolua_MySelf_AddDynamicDigitLabel00
static int tolua_MySelf_AddDynamicDigitLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIWidget* pRoot = ((UIWidget*)  tolua_tousertype(tolua_S,1,0));
  const char* szLabelName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float fDuration = ((float)  tolua_tonumber(tolua_S,3,0));
  int nBeginValue = ((int)  tolua_tonumber(tolua_S,4,0));
  int nEndValue = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   AddDynamicDigitLabel(pRoot,szLabelName,fDuration,nBeginValue,nEndValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDynamicDigitLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RunProgressBarEffect */
#ifndef TOLUA_DISABLE_tolua_MySelf_RunProgressBarEffect00
static int tolua_MySelf_RunProgressBarEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCProgressTimer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCProgressTimer* progressTimer = ((CCProgressTimer*)  tolua_tousertype(tolua_S,1,0));
  float fDestPercent = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   RunProgressBarEffect(progressTimer,fDestPercent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunProgressBarEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SetWidgetName2Font */
#ifndef TOLUA_DISABLE_tolua_MySelf_SetWidgetName2Font00
static int tolua_MySelf_SetWidgetName2Font00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pFileName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   SetWidgetName2Font(pFileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidgetName2Font'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CreateWidgetFromJsonFile */
#ifndef TOLUA_DISABLE_tolua_MySelf_CreateWidgetFromJsonFile00
static int tolua_MySelf_CreateWidgetFromJsonFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pFileName = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   UIWidget* tolua_ret = (UIWidget*)  CreateWidgetFromJsonFile(pFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIWidget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateWidgetFromJsonFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CalcCostMS */
#ifndef TOLUA_DISABLE_tolua_MySelf_CalcCostMS00
static int tolua_MySelf_CalcCostMS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* str = ((char*)  tolua_tostring(tolua_S,1,""));
  {
   float tolua_ret = (float)  CalcCostMS(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalcCostMS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CalcCostMS2 */
#ifndef TOLUA_DISABLE_tolua_MySelf_CalcCostMS200
static int tolua_MySelf_CalcCostMS200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int index = ((int)  tolua_tonumber(tolua_S,1,0));
  char* str = ((char*)  tolua_tostring(tolua_S,2,0));
  {
   float tolua_ret = (float)  CalcCostMS2(index,str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalcCostMS2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  MyTestClass */
#ifndef TOLUA_DISABLE_tolua_MySelf_MyTestClass_Create00
static int tolua_MySelf_MyTestClass_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MyTestClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int a = ((int)  tolua_tonumber(tolua_S,2,0));
  char b = ((char)  tolua_tonumber(tolua_S,3,0));
  float c = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   MyTestClass* tolua_ret = (MyTestClass*)  MyTestClass::Create(a,b,c);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MyTestClass");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PRINT of class  MyTestClass */
#ifndef TOLUA_DISABLE_tolua_MySelf_MyTestClass_PRINT00
static int tolua_MySelf_MyTestClass_PRINT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyTestClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyTestClass* self = (MyTestClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PRINT'", NULL);
#endif
  {
   self->PRINT();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PRINT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TOTAL of class  MyTestClass */
#ifndef TOLUA_DISABLE_tolua_MySelf_MyTestClass_TOTAL00
static int tolua_MySelf_MyTestClass_TOTAL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MyTestClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MyTestClass* self = (MyTestClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TOTAL'", NULL);
#endif
  {
   int tolua_ret = (int)  self->TOTAL();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TOTAL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetString of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_GetString00
static int tolua_MySelf_DataMgr_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DataMgr* self = (DataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool tofile = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetString'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetString(key,tofile);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetString of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_SetString00
static int tolua_MySelf_DataMgr_SetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DataMgr* self = (DataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
  bool fromfile = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetString'", NULL);
#endif
  {
   self->SetString(key,value,fromfile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInt of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_GetInt00
static int tolua_MySelf_DataMgr_GetInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DataMgr* self = (DataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool tofile = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetInt(key,tofile);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInt of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_SetInt00
static int tolua_MySelf_DataMgr_SetInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DataMgr* self = (DataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
  bool fromfile = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInt'", NULL);
#endif
  {
   self->SetInt(key,value,fromfile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadFromFile of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_LoadFromFile00
static int tolua_MySelf_DataMgr_LoadFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DataMgr* self = (DataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFromFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadFromFile(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveToFile of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_SaveToFile00
static int tolua_MySelf_DataMgr_SaveToFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DataMgr* self = (DataMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveToFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SaveToFile(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveToFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedMgr of class  DataMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_DataMgr_sharedMgr00
static int tolua_MySelf_DataMgr_sharedMgr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DataMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DataMgr* tolua_ret = (DataMgr*)  DataMgr::sharedMgr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DataMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedMgr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedMgr of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_sharedMgr00
static int tolua_MySelf_NetworkMgr_sharedMgr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   NetworkMgr* tolua_ret = (NetworkMgr*)  NetworkMgr::sharedMgr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"NetworkMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedMgr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ConnectServer of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_ConnectServer00
static int tolua_MySelf_NetworkMgr_ConnectServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ConnectServer'", NULL);
#endif
  {
   self->ConnectServer(ip,port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConnectServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CloseServer of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_CloseServer00
static int tolua_MySelf_NetworkMgr_CloseServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CloseServer'", NULL);
#endif
  {
   self->CloseServer();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CloseServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNetworkType of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_GetNetworkType00
static int tolua_MySelf_NetworkMgr_GetNetworkType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNetworkType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNetworkType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNetworkType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnMarshalIntFromProtocol of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_UnMarshalIntFromProtocol00
static int tolua_MySelf_NetworkMgr_UnMarshalIntFromProtocol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
  int pType = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* valueType = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnMarshalIntFromProtocol'", NULL);
#endif
  {
   int tolua_ret = (int)  self->UnMarshalIntFromProtocol(pType,valueType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnMarshalIntFromProtocol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarshalProtocolStart of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_MarshalProtocolStart00
static int tolua_MySelf_NetworkMgr_MarshalProtocolStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
  int protocolType = ((int)  tolua_tonumber(tolua_S,2,0));
  int pType = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarshalProtocolStart'", NULL);
#endif
  {
   self->MarshalProtocolStart(protocolType,pType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarshalProtocolStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarshalIntToProtocol of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_MarshalIntToProtocol00
static int tolua_MySelf_NetworkMgr_MarshalIntToProtocol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* valueType = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarshalIntToProtocol'", NULL);
#endif
  {
   self->MarshalIntToProtocol(valueType,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarshalIntToProtocol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarshalStringToProtocol of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_MarshalStringToProtocol00
static int tolua_MySelf_NetworkMgr_MarshalStringToProtocol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* valueType = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarshalStringToProtocol'", NULL);
#endif
  {
   self->MarshalStringToProtocol(valueType,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarshalStringToProtocol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarshalProtocolEndAndSend of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_MarshalProtocolEndAndSend00
static int tolua_MySelf_NetworkMgr_MarshalProtocolEndAndSend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarshalProtocolEndAndSend'", NULL);
#endif
  {
   self->MarshalProtocolEndAndSend();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarshalProtocolEndAndSend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: c2s_CmdGameDataSend of class  NetworkMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_NetworkMgr_c2s_CmdGameDataSend00
static int tolua_MySelf_NetworkMgr_c2s_CmdGameDataSend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkMgr* self = (NetworkMgr*)  tolua_tousertype(tolua_S,1,0);
  int cmd_header_type = ((int)  tolua_tonumber(tolua_S,2,0));
  void* pData = ((void*)  tolua_touserdata(tolua_S,3,0));
  int iSize = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'c2s_CmdGameDataSend'", NULL);
#endif
  {
   self->c2s_CmdGameDataSend(cmd_header_type,pData,iSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'c2s_CmdGameDataSend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  aeditor::AEParamAmmend */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_AEParamAmmend_create00
static int tolua_MySelf_aeditor_AEParamAmmend_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"aeditor::AEParamAmmend",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   aeditor::AEParamAmmend* tolua_ret = (aeditor::AEParamAmmend*)  aeditor::AEParamAmmend::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"aeditor::AEParamAmmend");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddPos of class  aeditor::AEParamAmmend */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_AEParamAmmend_AddPos00
static int tolua_MySelf_aeditor_AEParamAmmend_AddPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::AEParamAmmend",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::AEParamAmmend* self = (aeditor::AEParamAmmend*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  CCPoint* pos = ((CCPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddPos'", NULL);
#endif
  {
   self->AddPos(index,*pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSprite of class  aeditor::AEParamAmmend */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_AEParamAmmend_AddSprite00
static int tolua_MySelf_aeditor_AEParamAmmend_AddSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::AEParamAmmend",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::AEParamAmmend* self = (aeditor::AEParamAmmend*)  tolua_tousertype(tolua_S,1,0);
  std::string str = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSprite'", NULL);
#endif
  {
   self->AddSprite(str,node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  aeditor::ActionTemplateTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_ActionTemplateTable_create00
static int tolua_MySelf_aeditor_ActionTemplateTable_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"aeditor::ActionTemplateTable",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  CCScene* pScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  bool _isDebug = ((bool)  tolua_toboolean(tolua_S,4,false));
  {
   aeditor::ActionTemplateTable* tolua_ret = (aeditor::ActionTemplateTable*)  aeditor::ActionTemplateTable::create(fileName,pScene,_isDebug);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"aeditor::ActionTemplateTable");
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RunUIAction of class  aeditor::ActionTemplateTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_ActionTemplateTable_RunUIAction00
static int tolua_MySelf_aeditor_ActionTemplateTable_RunUIAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::ActionTemplateTable",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIWidget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::ActionTemplateTable* self = (aeditor::ActionTemplateTable*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  UIWidget* uiWidget = ((UIWidget*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RunUIAction'", NULL);
#endif
  {
   self->RunUIAction(fileName,uiWidget);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunUIAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RunAeAction of class  aeditor::ActionTemplateTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_ActionTemplateTable_RunAeAction00
static int tolua_MySelf_aeditor_ActionTemplateTable_RunAeAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::ActionTemplateTable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCCallFunc",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCCallFunc",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::ActionTemplateTable* self = (aeditor::ActionTemplateTable*)  tolua_tousertype(tolua_S,1,0);
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  CCCallFunc* onActionBefore = ((CCCallFunc*)  tolua_tousertype(tolua_S,4,NULL));
  CCCallFunc* onActionDone = ((CCCallFunc*)  tolua_tousertype(tolua_S,5,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RunAeAction'", NULL);
#endif
  {
   int tolua_ret = (int)  self->RunAeAction(container,fileName,onActionBefore,onActionDone);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunAeAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RunAeActionWithParam of class  aeditor::ActionTemplateTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_ActionTemplateTable_RunAeActionWithParam00
static int tolua_MySelf_aeditor_ActionTemplateTable_RunAeActionWithParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::ActionTemplateTable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"aeditor::AEParamAmmend",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCCallFunc",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"CCCallFunc",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::ActionTemplateTable* self = (aeditor::ActionTemplateTable*)  tolua_tousertype(tolua_S,1,0);
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  aeditor::AEParamAmmend* ammend = ((aeditor::AEParamAmmend*)  tolua_tousertype(tolua_S,4,0));
  CCCallFunc* onActionBefore = ((CCCallFunc*)  tolua_tousertype(tolua_S,5,NULL));
  CCCallFunc* onActionDone = ((CCCallFunc*)  tolua_tousertype(tolua_S,6,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RunAeActionWithParam'", NULL);
#endif
  {
   int tolua_ret = (int)  self->RunAeActionWithParam(container,fileName,ammend,onActionBefore,onActionDone);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunAeActionWithParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpriteByName of class  aeditor::ActionTemplateTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_ActionTemplateTable_GetSpriteByName00
static int tolua_MySelf_aeditor_ActionTemplateTable_GetSpriteByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::ActionTemplateTable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::ActionTemplateTable* self = (aeditor::ActionTemplateTable*)  tolua_tousertype(tolua_S,1,0);
  CCNode* container = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const std::string spriteName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpriteByName'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->GetSpriteByName(container,spriteName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCSprite");
   tolua_pushcppstring(tolua_S,(const char*)spriteName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpriteByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveByHandle of class  aeditor::ActionTemplateTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_aeditor_ActionTemplateTable_RemoveByHandle00
static int tolua_MySelf_aeditor_ActionTemplateTable_RemoveByHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aeditor::ActionTemplateTable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aeditor::ActionTemplateTable* self = (aeditor::ActionTemplateTable*)  tolua_tousertype(tolua_S,1,0);
  int handle = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveByHandle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveByHandle(handle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveByHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  GFuncMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GFuncMgr_GetInstance00
static int tolua_MySelf_GFuncMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GFuncMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GFuncMgr* tolua_ret = (GFuncMgr*)  GFuncMgr::GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GFuncMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddFunc of class  GFuncMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GFuncMgr_AddFunc00
static int tolua_MySelf_GFuncMgr_AddFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GFuncMgr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GFuncMgr* self = (GFuncMgr*)  tolua_tousertype(tolua_S,1,0);
  CCObject* obj = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  CCObject* parent = ((CCObject*)  tolua_tousertype(tolua_S,3,0));
  unsigned short event_type = ((unsigned short)  tolua_tonumber(tolua_S,4,0));
  std::string func_name = ((std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFunc'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddFunc(obj,parent,event_type,func_name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Fields of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_Fields00
static int tolua_MySelf_csvtable_Fields00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Fields'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Fields();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Fields'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Rows of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_Rows00
static int tolua_MySelf_csvtable_Rows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rows'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Rows();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Columns of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_Columns00
static int tolua_MySelf_csvtable_Columns00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Columns'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Columns();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Columns'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRecByColName of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_GetRecByColName00
static int tolua_MySelf_csvtable_GetRecByColName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
  int keyid = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* col_name = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRecByColName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetRecByColName(keyid,col_name);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRecByColName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRecByColIndex of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_GetRecByColIndex00
static int tolua_MySelf_csvtable_GetRecByColIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
  int keyid = ((int)  tolua_tonumber(tolua_S,2,0));
  int col_index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRecByColIndex'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetRecByColIndex(keyid,col_index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRecByColIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRecFromIndex of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_GetRecFromIndex00
static int tolua_MySelf_csvtable_GetRecFromIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
  int RowIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int ColIndex = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRecFromIndex'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetRecFromIndex(RowIndex,ColIndex);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRecFromIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColIndex of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_GetColIndex00
static int tolua_MySelf_csvtable_GetColIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
  const char* col_name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetColIndex(col_name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRowIndex of class  csvtable */
#ifndef TOLUA_DISABLE_tolua_MySelf_csvtable_GetRowIndex00
static int tolua_MySelf_csvtable_GetRowIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"csvtable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  csvtable* self = (csvtable*)  tolua_tousertype(tolua_S,1,0);
  int keyid = ((int)  tolua_tonumber(tolua_S,2,0));
  int aux_col_index = ((int)  tolua_tonumber(tolua_S,3,-1));
  int aux_keyid = ((int)  tolua_tonumber(tolua_S,4,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRowIndex(keyid,aux_col_index,aux_keyid);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: InitDataTables */
#ifndef TOLUA_DISABLE_tolua_MySelf_InitDataTables00
static int tolua_MySelf_InitDataTables00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  int table_type = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  InitDataTables(path,file,table_type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitDataTables'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetTable */
#ifndef TOLUA_DISABLE_tolua_MySelf_GetTable00
static int tolua_MySelf_GetTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   csvtable* tolua_ret = (csvtable*)  GetTable(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"csvtable");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  download_param */
#ifndef TOLUA_DISABLE_tolua_MySelf_download_param_create00
static int tolua_MySelf_download_param_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"download_param",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,8,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,9,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,10,"CCCallFunc",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string _src = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string _des = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string _sub_path = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  std::string _filename = ((std::string)  tolua_tocppstring(tolua_S,5,0));
  int _timeout = ((int)  tolua_tonumber(tolua_S,6,0));
  int _trytime = ((int)  tolua_tonumber(tolua_S,7,0));
  bool _use_base64 = ((bool)  tolua_toboolean(tolua_S,8,0));
  bool _use_resume = ((bool)  tolua_toboolean(tolua_S,9,0));
  CCCallFunc* _script_download_finish_func = ((CCCallFunc*)  tolua_tousertype(tolua_S,10,0));
  {
   download_param* tolua_ret = (download_param*)  download_param::create(_src,_des,_sub_path,_filename,_timeout,_trytime,_use_base64,_use_resume,_script_download_finish_func);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"download_param");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRet of class  download_param */
#ifndef TOLUA_DISABLE_tolua_MySelf_download_param_getRet00
static int tolua_MySelf_download_param_getRet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const download_param",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const download_param* self = (const download_param*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getRet();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  update_param */
#ifndef TOLUA_DISABLE_tolua_MySelf_update_param_create00
static int tolua_MySelf_update_param_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"update_param",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string _resource_path = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string _download_path = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string _src = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  std::string _md5_file = ((std::string)  tolua_tocppstring(tolua_S,5,0));
  int _timeout = ((int)  tolua_tonumber(tolua_S,6,0));
  int _trytime = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   update_param* tolua_ret = (update_param*)  update_param::create(_resource_path,_download_path,_src,_md5_file,_timeout,_trytime);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"update_param");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRet of class  update_param */
#ifndef TOLUA_DISABLE_tolua_MySelf_update_param_getRet00
static int tolua_MySelf_update_param_getRet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const update_param",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const update_param* self = (const update_param*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getRet();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  AssetsUpdateManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_AssetsUpdateManager_GetInstance00
static int tolua_MySelf_AssetsUpdateManager_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AssetsUpdateManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AssetsUpdateManager* tolua_ret = (AssetsUpdateManager*)  AssetsUpdateManager::GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AssetsUpdateManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckUpdate of class  AssetsUpdateManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_AssetsUpdateManager_CheckUpdate00
static int tolua_MySelf_AssetsUpdateManager_CheckUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsUpdateManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"update_param",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsUpdateManager* self = (AssetsUpdateManager*)  tolua_tousertype(tolua_S,1,0);
  update_param* pup = ((update_param*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckUpdate(pup);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDocumentPath of class  AssetsUpdateManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_AssetsUpdateManager_GetDocumentPath00
static int tolua_MySelf_AssetsUpdateManager_GetDocumentPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsUpdateManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsUpdateManager* self = (AssetsUpdateManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDocumentPath'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetDocumentPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDocumentPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTmpPath of class  AssetsUpdateManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_AssetsUpdateManager_GetTmpPath00
static int tolua_MySelf_AssetsUpdateManager_GetTmpPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsUpdateManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsUpdateManager* self = (AssetsUpdateManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTmpPath'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetTmpPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTmpPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCachePath of class  AssetsUpdateManager */
#ifndef TOLUA_DISABLE_tolua_MySelf_AssetsUpdateManager_GetCachePath00
static int tolua_MySelf_AssetsUpdateManager_GetCachePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsUpdateManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsUpdateManager* self = (AssetsUpdateManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCachePath'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->GetCachePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCachePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  aStar */
#ifndef TOLUA_DISABLE_tolua_MySelf_aStar_GetNext00
static int tolua_MySelf_aStar_GetNext00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aStar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aStar* self = (aStar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   aStar* tolua_ret = (aStar*)  self->GetNext();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"aStar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetX of class  aStar */
#ifndef TOLUA_DISABLE_tolua_MySelf_aStar_GetX00
static int tolua_MySelf_aStar_GetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aStar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aStar* self = (aStar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetY of class  aStar */
#ifndef TOLUA_DISABLE_tolua_MySelf_aStar_GetY00
static int tolua_MySelf_aStar_GetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aStar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aStar* self = (aStar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetY'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Release of class  aStar */
#ifndef TOLUA_DISABLE_tolua_MySelf_aStar_Release00
static int tolua_MySelf_aStar_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"aStar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  aStar* self = (aStar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Release'", NULL);
#endif
  {
   self->Release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  GMapMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GMapMgr_GetInstance00
static int tolua_MySelf_GMapMgr_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GMapMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GMapMgr* tolua_ret = (GMapMgr*)  GMapMgr::GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GMapMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxSize of class  GMapMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GMapMgr_SetMaxSize00
static int tolua_MySelf_GMapMgr_SetMaxSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapMgr* self = (GMapMgr*)  tolua_tousertype(tolua_S,1,0);
  int max_row = ((int)  tolua_tonumber(tolua_S,2,0));
  int max_col = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxSize'", NULL);
#endif
  {
   self->SetMaxSize(max_row,max_col);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMapGrid of class  GMapMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GMapMgr_SetMapGrid00
static int tolua_MySelf_GMapMgr_SetMapGrid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapMgr* self = (GMapMgr*)  tolua_tousertype(tolua_S,1,0);
  int row = ((int)  tolua_tonumber(tolua_S,2,0));
  int col = ((int)  tolua_tonumber(tolua_S,3,0));
  unsigned char grid = ((unsigned char)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMapGrid'", NULL);
#endif
  {
   self->SetMapGrid(row,col,grid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMapGrid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMapGrid of class  GMapMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GMapMgr_GetMapGrid00
static int tolua_MySelf_GMapMgr_GetMapGrid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapMgr* self = (GMapMgr*)  tolua_tousertype(tolua_S,1,0);
  int row = ((int)  tolua_tonumber(tolua_S,2,0));
  int col = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMapGrid'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMapGrid(row,col);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMapGrid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AStarStart of class  GMapMgr */
#ifndef TOLUA_DISABLE_tolua_MySelf_GMapMgr_AStarStart00
static int tolua_MySelf_GMapMgr_AStarStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GMapMgr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GMapMgr* self = (GMapMgr*)  tolua_tousertype(tolua_S,1,0);
  int X = ((int)  tolua_tonumber(tolua_S,2,0));
  int Y = ((int)  tolua_tonumber(tolua_S,3,0));
  int xE = ((int)  tolua_tonumber(tolua_S,4,0));
  int yE = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AStarStart'", NULL);
#endif
  {
   aStar* tolua_ret = (aStar*)  self->AStarStart(X,Y,xE,yE);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"aStar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AStarStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_MySelf_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIInputManager","UIInputManager","",tolua_collect_UIInputManager);
  #else
  tolua_cclass(tolua_S,"UIInputManager","UIInputManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIInputManager");
   tolua_function(tolua_S,"new",tolua_MySelf_UIInputManager_new00);
   tolua_function(tolua_S,"new_local",tolua_MySelf_UIInputManager_new00_local);
   tolua_function(tolua_S,".call",tolua_MySelf_UIInputManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_MySelf_UIInputManager_delete00);
   tolua_function(tolua_S,"registWidget",tolua_MySelf_UIInputManager_registWidget00);
   tolua_function(tolua_S,"uiSceneHasChanged",tolua_MySelf_UIInputManager_uiSceneHasChanged00);
   tolua_function(tolua_S,"sortWidgets",tolua_MySelf_UIInputManager_sortWidgets00);
   tolua_function(tolua_S,"sortRootWidgets",tolua_MySelf_UIInputManager_sortRootWidgets00);
   tolua_function(tolua_S,"removeManageredWidget",tolua_MySelf_UIInputManager_removeManageredWidget00);
   tolua_function(tolua_S,"checkEventWidget",tolua_MySelf_UIInputManager_checkEventWidget00);
   tolua_function(tolua_S,"addCheckedDoubleClickWidget",tolua_MySelf_UIInputManager_addCheckedDoubleClickWidget00);
   tolua_function(tolua_S,"update",tolua_MySelf_UIInputManager_update00);
   tolua_function(tolua_S,"onTouchBegan",tolua_MySelf_UIInputManager_onTouchBegan00);
   tolua_function(tolua_S,"onTouchMoved",tolua_MySelf_UIInputManager_onTouchMoved00);
   tolua_function(tolua_S,"onTouchEnd",tolua_MySelf_UIInputManager_onTouchEnd00);
   tolua_function(tolua_S,"onTouchCancelled",tolua_MySelf_UIInputManager_onTouchCancelled00);
   tolua_function(tolua_S,"setRootWidget",tolua_MySelf_UIInputManager_setRootWidget00);
   tolua_function(tolua_S,"getRootWidget",tolua_MySelf_UIInputManager_getRootWidget00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UILayer","UILayer","CCLayer",NULL);
  tolua_beginmodule(tolua_S,"UILayer");
   tolua_function(tolua_S,"create",tolua_MySelf_UILayer_create00);
   tolua_function(tolua_S,"onEnter",tolua_MySelf_UILayer_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_MySelf_UILayer_onExit00);
   tolua_function(tolua_S,"onEnterTransitionDidFinish",tolua_MySelf_UILayer_onEnterTransitionDidFinish00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_MySelf_UILayer_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_MySelf_UILayer_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_MySelf_UILayer_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_MySelf_UILayer_ccTouchCancelled00);
   tolua_function(tolua_S,"scheduleUpdate",tolua_MySelf_UILayer_scheduleUpdate00);
   tolua_function(tolua_S,"addWidget",tolua_MySelf_UILayer_addWidget00);
   tolua_function(tolua_S,"removeWidgetAndCleanUp",tolua_MySelf_UILayer_removeWidgetAndCleanUp00);
   tolua_function(tolua_S,"setVisible",tolua_MySelf_UILayer_setVisible00);
   tolua_function(tolua_S,"update",tolua_MySelf_UILayer_update00);
   tolua_function(tolua_S,"addUpdateEnableWidget",tolua_MySelf_UILayer_addUpdateEnableWidget00);
   tolua_function(tolua_S,"removeUpdateEnableWidget",tolua_MySelf_UILayer_removeUpdateEnableWidget00);
   tolua_function(tolua_S,"getWidgetByTag",tolua_MySelf_UILayer_getWidgetByTag00);
   tolua_function(tolua_S,"getWidgetByName",tolua_MySelf_UILayer_getWidgetByName00);
   tolua_function(tolua_S,"getInputManager",tolua_MySelf_UILayer_getInputManager00);
   tolua_function(tolua_S,"clear",tolua_MySelf_UILayer_clear00);
   tolua_function(tolua_S,"dispose",tolua_MySelf_UILayer_dispose00);
   tolua_function(tolua_S,"getRootWidget",tolua_MySelf_UILayer_getRootWidget00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIRootWidget","UIRootWidget","UIContainerWidget",tolua_collect_UIRootWidget);
  #else
  tolua_cclass(tolua_S,"UIRootWidget","UIRootWidget","UIContainerWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIRootWidget");
   tolua_function(tolua_S,"new",tolua_MySelf_UIRootWidget_new00);
   tolua_function(tolua_S,"new_local",tolua_MySelf_UIRootWidget_new00_local);
   tolua_function(tolua_S,".call",tolua_MySelf_UIRootWidget_new00_local);
   tolua_function(tolua_S,"delete",tolua_MySelf_UIRootWidget_delete00);
   tolua_function(tolua_S,"create",tolua_MySelf_UIRootWidget_create00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"UI_TEX_TYPE_LOCAL",UI_TEX_TYPE_LOCAL);
  tolua_constant(tolua_S,"UI_TEX_TYPE_PLIST",UI_TEX_TYPE_PLIST);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIWidget","UIWidget","CCObject",tolua_collect_UIWidget);
  #else
  tolua_cclass(tolua_S,"UIWidget","UIWidget","CCObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIWidget");
   tolua_function(tolua_S,"new",tolua_MySelf_UIWidget_new00);
   tolua_function(tolua_S,"new_local",tolua_MySelf_UIWidget_new00_local);
   tolua_function(tolua_S,".call",tolua_MySelf_UIWidget_new00_local);
   tolua_function(tolua_S,"delete",tolua_MySelf_UIWidget_delete00);
   tolua_function(tolua_S,"releaseResoures",tolua_MySelf_UIWidget_releaseResoures00);
   tolua_function(tolua_S,"create",tolua_MySelf_UIWidget_create00);
   tolua_function(tolua_S,"initPressState",tolua_MySelf_UIWidget_initPressState00);
   tolua_function(tolua_S,"setPressState",tolua_MySelf_UIWidget_setPressState00);
   tolua_function(tolua_S,"addChild",tolua_MySelf_UIWidget_addChild00);
   tolua_function(tolua_S,"removeChild",tolua_MySelf_UIWidget_removeChild00);
   tolua_function(tolua_S,"removeFromParentAndCleanup",tolua_MySelf_UIWidget_removeFromParentAndCleanup00);
   tolua_function(tolua_S,"removeAllChildrenAndCleanUp",tolua_MySelf_UIWidget_removeAllChildrenAndCleanUp00);
   tolua_function(tolua_S,"setWidgetZOrder",tolua_MySelf_UIWidget_setWidgetZOrder00);
   tolua_function(tolua_S,"getWidgetZOrder",tolua_MySelf_UIWidget_getWidgetZOrder00);
   tolua_function(tolua_S,"reorderChild",tolua_MySelf_UIWidget_reorderChild00);
   tolua_function(tolua_S,"setTouchEnable",tolua_MySelf_UIWidget_setTouchEnable00);
   tolua_function(tolua_S,"updateChildrenTouchEnable",tolua_MySelf_UIWidget_updateChildrenTouchEnable00);
   tolua_function(tolua_S,"isTouchEnable",tolua_MySelf_UIWidget_isTouchEnable00);
   tolua_function(tolua_S,"setUpdateEnable",tolua_MySelf_UIWidget_setUpdateEnable00);
   tolua_function(tolua_S,"getUpdateEnable",tolua_MySelf_UIWidget_getUpdateEnable00);
   tolua_function(tolua_S,"isFocus",tolua_MySelf_UIWidget_isFocus00);
   tolua_function(tolua_S,"setFocus",tolua_MySelf_UIWidget_setFocus00);
   tolua_function(tolua_S,"disable",tolua_MySelf_UIWidget_disable00);
   tolua_function(tolua_S,"active",tolua_MySelf_UIWidget_active00);
   tolua_function(tolua_S,"updateChildrenActive",tolua_MySelf_UIWidget_updateChildrenActive00);
   tolua_function(tolua_S,"updateChildrenDisable",tolua_MySelf_UIWidget_updateChildrenDisable00);
   tolua_function(tolua_S,"isActive",tolua_MySelf_UIWidget_isActive00);
   tolua_function(tolua_S,"updateBeTouchEnable",tolua_MySelf_UIWidget_updateBeTouchEnable00);
   tolua_function(tolua_S,"setVisible",tolua_MySelf_UIWidget_setVisible00);
   tolua_function(tolua_S,"isVisible",tolua_MySelf_UIWidget_isVisible00);
   tolua_function(tolua_S,"getRect",tolua_MySelf_UIWidget_getRect00);
   tolua_function(tolua_S,"getRelativeRect",tolua_MySelf_UIWidget_getRelativeRect00);
   tolua_function(tolua_S,"getContentSize",tolua_MySelf_UIWidget_getContentSize00);
   tolua_function(tolua_S,"getLocationInWindow",tolua_MySelf_UIWidget_getLocationInWindow00);
   tolua_function(tolua_S,"getRelativeLeftPos",tolua_MySelf_UIWidget_getRelativeLeftPos00);
   tolua_function(tolua_S,"getRelativeBottomPos",tolua_MySelf_UIWidget_getRelativeBottomPos00);
   tolua_function(tolua_S,"getRelativeRightPos",tolua_MySelf_UIWidget_getRelativeRightPos00);
   tolua_function(tolua_S,"getRelativeTopPos",tolua_MySelf_UIWidget_getRelativeTopPos00);
   tolua_function(tolua_S,"getValidNode",tolua_MySelf_UIWidget_getValidNode00);
   tolua_function(tolua_S,"getContainerNode",tolua_MySelf_UIWidget_getContainerNode00);
   tolua_function(tolua_S,"setWidgetParent",tolua_MySelf_UIWidget_setWidgetParent00);
   tolua_function(tolua_S,"getWidgetParent",tolua_MySelf_UIWidget_getWidgetParent00);
   tolua_function(tolua_S,"getChildByName",tolua_MySelf_UIWidget_getChildByName00);
   tolua_function(tolua_S,"getChildByTag",tolua_MySelf_UIWidget_getChildByTag00);
   tolua_function(tolua_S,"getChildren",tolua_MySelf_UIWidget_getChildren00);
   tolua_function(tolua_S,"addPushDownEvent",tolua_MySelf_UIWidget_addPushDownEvent00);
   tolua_function(tolua_S,"addMoveEvent",tolua_MySelf_UIWidget_addMoveEvent00);
   tolua_function(tolua_S,"addReleaseEvent",tolua_MySelf_UIWidget_addReleaseEvent00);
   tolua_function(tolua_S,"addCancelEvent",tolua_MySelf_UIWidget_addCancelEvent00);
   tolua_function(tolua_S,"setPosition",tolua_MySelf_UIWidget_setPosition00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_MySelf_UIWidget_setAnchorPoint00);
   tolua_function(tolua_S,"updateAnchorPoint",tolua_MySelf_UIWidget_updateAnchorPoint00);
   tolua_function(tolua_S,"getPosition",tolua_MySelf_UIWidget_getPosition00);
   tolua_function(tolua_S,"getAnchorPoint",tolua_MySelf_UIWidget_getAnchorPoint00);
   tolua_function(tolua_S,"setScale",tolua_MySelf_UIWidget_setScale00);
   tolua_function(tolua_S,"getScale",tolua_MySelf_UIWidget_getScale00);
   tolua_function(tolua_S,"setScaleX",tolua_MySelf_UIWidget_setScaleX00);
   tolua_function(tolua_S,"getScaleX",tolua_MySelf_UIWidget_getScaleX00);
   tolua_function(tolua_S,"setScaleY",tolua_MySelf_UIWidget_setScaleY00);
   tolua_function(tolua_S,"getScaleY",tolua_MySelf_UIWidget_getScaleY00);
   tolua_function(tolua_S,"onScaleDirtyChanged",tolua_MySelf_UIWidget_onScaleDirtyChanged00);
   tolua_function(tolua_S,"onScaleXDirtyChanged",tolua_MySelf_UIWidget_onScaleXDirtyChanged00);
   tolua_function(tolua_S,"onScaleYDirtyChanged",tolua_MySelf_UIWidget_onScaleYDirtyChanged00);
   tolua_function(tolua_S,"setRotation",tolua_MySelf_UIWidget_setRotation00);
   tolua_function(tolua_S,"getRotation",tolua_MySelf_UIWidget_getRotation00);
   tolua_function(tolua_S,"setRotationX",tolua_MySelf_UIWidget_setRotationX00);
   tolua_function(tolua_S,"getRotationX",tolua_MySelf_UIWidget_getRotationX00);
   tolua_function(tolua_S,"setRotationY",tolua_MySelf_UIWidget_setRotationY00);
   tolua_function(tolua_S,"getRotationY",tolua_MySelf_UIWidget_getRotationY00);
   tolua_function(tolua_S,"setSkewX",tolua_MySelf_UIWidget_setSkewX00);
   tolua_function(tolua_S,"getSkewX",tolua_MySelf_UIWidget_getSkewX00);
   tolua_function(tolua_S,"setSkewY",tolua_MySelf_UIWidget_setSkewY00);
   tolua_function(tolua_S,"getSkewY",tolua_MySelf_UIWidget_getSkewY00);
   tolua_function(tolua_S,"setFlipX",tolua_MySelf_UIWidget_setFlipX00);
   tolua_function(tolua_S,"isFlipX",tolua_MySelf_UIWidget_isFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_MySelf_UIWidget_setFlipY00);
   tolua_function(tolua_S,"isFlipY",tolua_MySelf_UIWidget_isFlipY00);
   tolua_function(tolua_S,"setColor",tolua_MySelf_UIWidget_setColor00);
   tolua_function(tolua_S,"getColor",tolua_MySelf_UIWidget_getColor00);
   tolua_function(tolua_S,"setOpacity",tolua_MySelf_UIWidget_setOpacity00);
   tolua_function(tolua_S,"getOpacity",tolua_MySelf_UIWidget_getOpacity00);
   tolua_function(tolua_S,"isCascadeOpacityEnabled",tolua_MySelf_UIWidget_isCascadeOpacityEnabled00);
   tolua_function(tolua_S,"setCascadeOpacityEnabled",tolua_MySelf_UIWidget_setCascadeOpacityEnabled00);
   tolua_function(tolua_S,"isCascadeColorEnabled",tolua_MySelf_UIWidget_isCascadeColorEnabled00);
   tolua_function(tolua_S,"setCascadeColorEnabled",tolua_MySelf_UIWidget_setCascadeColorEnabled00);
   tolua_function(tolua_S,"setBlendFunc",tolua_MySelf_UIWidget_setBlendFunc00);
   tolua_function(tolua_S,"setActionManager",tolua_MySelf_UIWidget_setActionManager00);
   tolua_function(tolua_S,"getActionManager",tolua_MySelf_UIWidget_getActionManager00);
   tolua_function(tolua_S,"runAction",tolua_MySelf_UIWidget_runAction00);
   tolua_function(tolua_S,"stopAllActions",tolua_MySelf_UIWidget_stopAllActions00);
   tolua_function(tolua_S,"stopAction",tolua_MySelf_UIWidget_stopAction00);
   tolua_function(tolua_S,"stopActionByTag",tolua_MySelf_UIWidget_stopActionByTag00);
   tolua_function(tolua_S,"getActionByTag",tolua_MySelf_UIWidget_getActionByTag00);
   tolua_function(tolua_S,"setActionTag",tolua_MySelf_UIWidget_setActionTag00);
   tolua_function(tolua_S,"getActionTag",tolua_MySelf_UIWidget_getActionTag00);
   tolua_function(tolua_S,"setNeedCheckVisibleDepandParent",tolua_MySelf_UIWidget_setNeedCheckVisibleDepandParent00);
   tolua_function(tolua_S,"didNotSelectSelf",tolua_MySelf_UIWidget_didNotSelectSelf00);
   tolua_function(tolua_S,"onTouchBegan",tolua_MySelf_UIWidget_onTouchBegan00);
   tolua_function(tolua_S,"onTouchMoved",tolua_MySelf_UIWidget_onTouchMoved00);
   tolua_function(tolua_S,"onTouchEnded",tolua_MySelf_UIWidget_onTouchEnded00);
   tolua_function(tolua_S,"onTouchCancelled",tolua_MySelf_UIWidget_onTouchCancelled00);
   tolua_function(tolua_S,"onTouchLongClicked",tolua_MySelf_UIWidget_onTouchLongClicked00);
   tolua_function(tolua_S,"isClippingEnable",tolua_MySelf_UIWidget_isClippingEnable00);
   tolua_function(tolua_S,"update",tolua_MySelf_UIWidget_update00);
   tolua_function(tolua_S,"pointAtSelfBody",tolua_MySelf_UIWidget_pointAtSelfBody00);
   tolua_function(tolua_S,"checkVisibleDependParent",tolua_MySelf_UIWidget_checkVisibleDependParent00);
   tolua_function(tolua_S,"checkChildInfo",tolua_MySelf_UIWidget_checkChildInfo00);
   tolua_function(tolua_S,"getAbsoluteScaleX",tolua_MySelf_UIWidget_getAbsoluteScaleX00);
   tolua_function(tolua_S,"getAbsoluteScaleY",tolua_MySelf_UIWidget_getAbsoluteScaleY00);
   tolua_function(tolua_S,"getAbsoluteVisible",tolua_MySelf_UIWidget_getAbsoluteVisible00);
   tolua_function(tolua_S,"updateChildrenVisibleDirty",tolua_MySelf_UIWidget_updateChildrenVisibleDirty00);
   tolua_function(tolua_S,"updateChildrenOpacityDirty",tolua_MySelf_UIWidget_updateChildrenOpacityDirty00);
   tolua_function(tolua_S,"adaptSize",tolua_MySelf_UIWidget_adaptSize00);
   tolua_function(tolua_S,"setCreateFromFile",tolua_MySelf_UIWidget_setCreateFromFile00);
   tolua_function(tolua_S,"setFileDesignSize",tolua_MySelf_UIWidget_setFileDesignSize00);
   tolua_function(tolua_S,"getFileDesignSize",tolua_MySelf_UIWidget_getFileDesignSize00);
   tolua_function(tolua_S,"setUILayer",tolua_MySelf_UIWidget_setUILayer00);
   tolua_function(tolua_S,"updateChildrenUILayer",tolua_MySelf_UIWidget_updateChildrenUILayer00);
   tolua_function(tolua_S,"structureChangedEvent",tolua_MySelf_UIWidget_structureChangedEvent00);
   tolua_function(tolua_S,"disableUpdate",tolua_MySelf_UIWidget_disableUpdate00);
   tolua_function(tolua_S,"getTouchStartPos",tolua_MySelf_UIWidget_getTouchStartPos00);
   tolua_function(tolua_S,"getTouchMovePos",tolua_MySelf_UIWidget_getTouchMovePos00);
   tolua_function(tolua_S,"getTouchEndPos",tolua_MySelf_UIWidget_getTouchEndPos00);
   tolua_function(tolua_S,"setWidgetTag",tolua_MySelf_UIWidget_setWidgetTag00);
   tolua_function(tolua_S,"getWidgetTag",tolua_MySelf_UIWidget_getWidgetTag00);
   tolua_function(tolua_S,"setName",tolua_MySelf_UIWidget_setName00);
   tolua_function(tolua_S,"getName",tolua_MySelf_UIWidget_getName00);
   tolua_function(tolua_S,"getWidgetType",tolua_MySelf_UIWidget_getWidgetType00);
   tolua_function(tolua_S,"getWidgetName",tolua_MySelf_UIWidget_getWidgetName00);
   tolua_function(tolua_S,"setBindingAction",tolua_MySelf_UIWidget_setBindingAction00);
   tolua_variable(tolua_S,"__UILayoutUnit__",tolua_get_UIWidget___UILayoutUnit__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIHelper","UIHelper","",NULL);
  tolua_beginmodule(tolua_S,"UIHelper");
   tolua_function(tolua_S,"createWidgetFromJsonFile",tolua_MySelf_UIHelper_createWidgetFromJsonFile00);
   tolua_function(tolua_S,"instance",tolua_MySelf_UIHelper_instance00);
   tolua_function(tolua_S,"purgeUIHelper",tolua_MySelf_UIHelper_purgeUIHelper00);
   tolua_function(tolua_S,"addSpriteFrame",tolua_MySelf_UIHelper_addSpriteFrame00);
   tolua_function(tolua_S,"removeSpriteFrame",tolua_MySelf_UIHelper_removeSpriteFrame00);
   tolua_function(tolua_S,"removeAllSpriteFrame",tolua_MySelf_UIHelper_removeAllSpriteFrame00);
   tolua_function(tolua_S,"seekWidgetByTag",tolua_MySelf_UIHelper_seekWidgetByTag00);
   tolua_function(tolua_S,"seekWidgetByName",tolua_MySelf_UIHelper_seekWidgetByName00);
   tolua_function(tolua_S,"seekActionWidgetByActionTag",tolua_MySelf_UIHelper_seekActionWidgetByActionTag00);
   tolua_function(tolua_S,"seekWidgetByRelativeName",tolua_MySelf_UIHelper_seekWidgetByRelativeName00);
   tolua_function(tolua_S,"setFileDesignWidth",tolua_MySelf_UIHelper_setFileDesignWidth00);
   tolua_function(tolua_S,"getFileDesignWidth",tolua_MySelf_UIHelper_getFileDesignWidth00);
   tolua_function(tolua_S,"setFileDesignHeight",tolua_MySelf_UIHelper_setFileDesignHeight00);
   tolua_function(tolua_S,"getFileDesignHeight",tolua_MySelf_UIHelper_getFileDesignHeight00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIButton","UIButton","UIWidget",NULL);
  tolua_beginmodule(tolua_S,"UIButton");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIImageView","UIImageView","UIWidget",NULL);
  tolua_beginmodule(tolua_S,"UIImageView");
   tolua_function(tolua_S,"create",tolua_MySelf_UIImageView_create00);
   tolua_function(tolua_S,"setTexture",tolua_MySelf_UIImageView_setTexture00);
   tolua_function(tolua_S,"setTextureRect",tolua_MySelf_UIImageView_setTextureRect00);
   tolua_function(tolua_S,"doubleClickEvent",tolua_MySelf_UIImageView_doubleClickEvent00);
   tolua_function(tolua_S,"checkDoubleClick",tolua_MySelf_UIImageView_checkDoubleClick00);
   tolua_function(tolua_S,"setDoubleClickEnable",tolua_MySelf_UIImageView_setDoubleClickEnable00);
   tolua_function(tolua_S,"setFlipX",tolua_MySelf_UIImageView_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_MySelf_UIImageView_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_MySelf_UIImageView_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_MySelf_UIImageView_isFlipY00);
   tolua_function(tolua_S,"setScale9Enable",tolua_MySelf_UIImageView_setScale9Enable00);
   tolua_function(tolua_S,"setScale9Size",tolua_MySelf_UIImageView_setScale9Size00);
   tolua_function(tolua_S,"setDisplayFrame",tolua_MySelf_UIImageView_setDisplayFrame00);
   tolua_function(tolua_S,"setSpriteFrame",tolua_MySelf_UIImageView_setSpriteFrame00);
   tolua_function(tolua_S,"setPreferredSize",tolua_MySelf_UIImageView_setPreferredSize00);
   tolua_function(tolua_S,"setInsetLeft",tolua_MySelf_UIImageView_setInsetLeft00);
   tolua_function(tolua_S,"setInsetTop",tolua_MySelf_UIImageView_setInsetTop00);
   tolua_function(tolua_S,"setInsetRight",tolua_MySelf_UIImageView_setInsetRight00);
   tolua_function(tolua_S,"setInsetBottom",tolua_MySelf_UIImageView_setInsetBottom00);
   tolua_function(tolua_S,"setCapInsets",tolua_MySelf_UIImageView_setCapInsets00);
   tolua_function(tolua_S,"getValidNode",tolua_MySelf_UIImageView_getValidNode00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_MySelf_UIImageView_setAnchorPoint00);
   tolua_function(tolua_S,"onTouchBegan",tolua_MySelf_UIImageView_onTouchBegan00);
   tolua_function(tolua_S,"onTouchEnded",tolua_MySelf_UIImageView_onTouchEnded00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UITextArea","UITextArea","UIWidget",tolua_collect_UITextArea);
  #else
  tolua_cclass(tolua_S,"UITextArea","UITextArea","UIWidget",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UITextArea");
   tolua_function(tolua_S,"new",tolua_MySelf_UITextArea_new00);
   tolua_function(tolua_S,"new_local",tolua_MySelf_UITextArea_new00_local);
   tolua_function(tolua_S,".call",tolua_MySelf_UITextArea_new00_local);
   tolua_function(tolua_S,"create",tolua_MySelf_UITextArea_create00);
   tolua_function(tolua_S,"initNodes",tolua_MySelf_UITextArea_initNodes00);
   tolua_function(tolua_S,"setText",tolua_MySelf_UITextArea_setText00);
   tolua_function(tolua_S,"setTextAreaSize",tolua_MySelf_UITextArea_setTextAreaSize00);
   tolua_function(tolua_S,"setTextHorizontalAlignment",tolua_MySelf_UITextArea_setTextHorizontalAlignment00);
   tolua_function(tolua_S,"setTextVerticalAlignment",tolua_MySelf_UITextArea_setTextVerticalAlignment00);
   tolua_function(tolua_S,"getStringLength",tolua_MySelf_UITextArea_getStringLength00);
   tolua_function(tolua_S,"getStringValue",tolua_MySelf_UITextArea_getStringValue00);
   tolua_function(tolua_S,"setTextColor",tolua_MySelf_UITextArea_setTextColor00);
   tolua_function(tolua_S,"setFontSize",tolua_MySelf_UITextArea_setFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_MySelf_UITextArea_setFontName00);
   tolua_function(tolua_S,"setFlipX",tolua_MySelf_UITextArea_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_MySelf_UITextArea_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_MySelf_UITextArea_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_MySelf_UITextArea_isFlipY00);
   tolua_function(tolua_S,"getValidNode",tolua_MySelf_UITextArea_getValidNode00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_MySelf_UITextArea_setAnchorPoint00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UILabel","UILabel","UIWidget",NULL);
  tolua_beginmodule(tolua_S,"UILabel");
   tolua_function(tolua_S,"create",tolua_MySelf_UILabel_create00);
   tolua_function(tolua_S,"setText",tolua_MySelf_UILabel_setText00);
   tolua_function(tolua_S,"setTextDefinition",tolua_MySelf_UILabel_setTextDefinition00);
   tolua_function(tolua_S,"getStringValue",tolua_MySelf_UILabel_getStringValue00);
   tolua_function(tolua_S,"getStringLength",tolua_MySelf_UILabel_getStringLength00);
   tolua_function(tolua_S,"setFontSize",tolua_MySelf_UILabel_setFontSize00);
   tolua_function(tolua_S,"setFontName",tolua_MySelf_UILabel_setFontName00);
   tolua_function(tolua_S,"getFontName",tolua_MySelf_UILabel_getFontName00);
   tolua_function(tolua_S,"setTouchScaleChangeAble",tolua_MySelf_UILabel_setTouchScaleChangeAble00);
   tolua_function(tolua_S,"getTouchScaleChangeAble",tolua_MySelf_UILabel_getTouchScaleChangeAble00);
   tolua_function(tolua_S,"clickScale",tolua_MySelf_UILabel_clickScale00);
   tolua_function(tolua_S,"setFlipX",tolua_MySelf_UILabel_setFlipX00);
   tolua_function(tolua_S,"setFlipY",tolua_MySelf_UILabel_setFlipY00);
   tolua_function(tolua_S,"isFlipX",tolua_MySelf_UILabel_isFlipX00);
   tolua_function(tolua_S,"isFlipY",tolua_MySelf_UILabel_isFlipY00);
   tolua_function(tolua_S,"setGravity",tolua_MySelf_UILabel_setGravity00);
   tolua_function(tolua_S,"adaptSize",tolua_MySelf_UILabel_adaptSize00);
   tolua_function(tolua_S,"getValidNode",tolua_MySelf_UILabel_getValidNode00);
   tolua_function(tolua_S,"setAnchorPoint",tolua_MySelf_UILabel_setAnchorPoint00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GET_PATH",tolua_MySelf_GET_PATH00);
  tolua_function(tolua_S,"GET_PATH2",tolua_MySelf_GET_PATH200);
  tolua_function(tolua_S,"STRING_WITH_INT",tolua_MySelf_STRING_WITH_INT00);
  tolua_function(tolua_S,"STRING_WITH_INT2",tolua_MySelf_STRING_WITH_INT200);
  tolua_function(tolua_S,"GET_WIN_SIZE",tolua_MySelf_GET_WIN_SIZE00);
  tolua_function(tolua_S,"GET_POS_CENTOR",tolua_MySelf_GET_POS_CENTOR00);
  tolua_function(tolua_S,"GET_CCOBJECT_DISTANCE",tolua_MySelf_GET_CCOBJECT_DISTANCE00);
  tolua_function(tolua_S,"GET_CCP_DISTANCE",tolua_MySelf_GET_CCP_DISTANCE00);
  tolua_function(tolua_S,"GET_CCP_ANGLE",tolua_MySelf_GET_CCP_ANGLE00);
  tolua_function(tolua_S,"RADIANS_TO_DEGREES",tolua_MySelf_RADIANS_TO_DEGREES00);
  tolua_function(tolua_S,"DEGREES_TO_RADIANS",tolua_MySelf_DEGREES_TO_RADIANS00);
  tolua_function(tolua_S,"SET_NODE_ZORDER",tolua_MySelf_SET_NODE_ZORDER00);
  tolua_function(tolua_S,"POINT_INT_NODE",tolua_MySelf_POINT_INT_NODE00);
  tolua_function(tolua_S,"SET_SPRITE_TEXTURE",tolua_MySelf_SET_SPRITE_TEXTURE00);
  tolua_function(tolua_S,"CreateStrideLabelContainer",tolua_MySelf_CreateStrideLabelContainer00);
  tolua_function(tolua_S,"CreateStrideLabelContainer",tolua_MySelf_CreateStrideLabelContainer01);
  tolua_function(tolua_S,"CreateStrideLabelContainer",tolua_MySelf_CreateStrideLabelContainer02);
  tolua_function(tolua_S,"CreateStrideLabelContainer",tolua_MySelf_CreateStrideLabelContainer03);
  tolua_function(tolua_S,"SetMultiColorLabelText",tolua_MySelf_SetMultiColorLabelText00);
  tolua_function(tolua_S,"SetWidgetAnchorPoint",tolua_MySelf_SetWidgetAnchorPoint00);
  tolua_function(tolua_S,"SetLabelColor",tolua_MySelf_SetLabelColor00);
  tolua_function(tolua_S,"SetTextAreaText",tolua_MySelf_SetTextAreaText00);
  tolua_function(tolua_S,"SetLabelText",tolua_MySelf_SetLabelText00);
  tolua_function(tolua_S,"SetLabelTextWithInt",tolua_MySelf_SetLabelTextWithInt00);
  tolua_function(tolua_S,"SetLabelTextWithIntSign",tolua_MySelf_SetLabelTextWithIntSign00);
  tolua_function(tolua_S,"GetLabelValue",tolua_MySelf_GetLabelValue00);
  tolua_function(tolua_S,"SetLabelAtlasText",tolua_MySelf_SetLabelAtlasText00);
  tolua_function(tolua_S,"SetLabelAtlasTextWithInt",tolua_MySelf_SetLabelAtlasTextWithInt00);
  tolua_function(tolua_S,"SetProgressBarPercent",tolua_MySelf_SetProgressBarPercent00);
  tolua_function(tolua_S,"HideWidget",tolua_MySelf_HideWidget00);
  tolua_function(tolua_S,"ShowWidget",tolua_MySelf_ShowWidget00);
  tolua_function(tolua_S,"SetTabHighlight",tolua_MySelf_SetTabHighlight00);
  tolua_function(tolua_S,"SetWidgetTag",tolua_MySelf_SetWidgetTag00);
  tolua_function(tolua_S,"EnableWidget",tolua_MySelf_EnableWidget00);
  tolua_function(tolua_S,"DisableWidget",tolua_MySelf_DisableWidget00);
  tolua_function(tolua_S,"GetWidgetPosition",tolua_MySelf_GetWidgetPosition00);
  tolua_function(tolua_S,"AddEffectToWidget",tolua_MySelf_AddEffectToWidget00);
  tolua_function(tolua_S,"AddDynamicDigitLabel",tolua_MySelf_AddDynamicDigitLabel00);
  tolua_function(tolua_S,"RunProgressBarEffect",tolua_MySelf_RunProgressBarEffect00);
  tolua_function(tolua_S,"SetWidgetName2Font",tolua_MySelf_SetWidgetName2Font00);
  tolua_function(tolua_S,"CreateWidgetFromJsonFile",tolua_MySelf_CreateWidgetFromJsonFile00);
  tolua_function(tolua_S,"CalcCostMS",tolua_MySelf_CalcCostMS00);
  tolua_function(tolua_S,"CalcCostMS2",tolua_MySelf_CalcCostMS200);
  tolua_cclass(tolua_S,"MyTestClass","MyTestClass","",NULL);
  tolua_beginmodule(tolua_S,"MyTestClass");
   tolua_function(tolua_S,"Create",tolua_MySelf_MyTestClass_Create00);
   tolua_function(tolua_S,"PRINT",tolua_MySelf_MyTestClass_PRINT00);
   tolua_function(tolua_S,"TOTAL",tolua_MySelf_MyTestClass_TOTAL00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DataMgr","DataMgr","",NULL);
  tolua_beginmodule(tolua_S,"DataMgr");
   tolua_function(tolua_S,"GetString",tolua_MySelf_DataMgr_GetString00);
   tolua_function(tolua_S,"SetString",tolua_MySelf_DataMgr_SetString00);
   tolua_function(tolua_S,"GetInt",tolua_MySelf_DataMgr_GetInt00);
   tolua_function(tolua_S,"SetInt",tolua_MySelf_DataMgr_SetInt00);
   tolua_function(tolua_S,"LoadFromFile",tolua_MySelf_DataMgr_LoadFromFile00);
   tolua_function(tolua_S,"SaveToFile",tolua_MySelf_DataMgr_SaveToFile00);
   tolua_function(tolua_S,"sharedMgr",tolua_MySelf_DataMgr_sharedMgr00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NetworkMgr","NetworkMgr","",NULL);
  tolua_beginmodule(tolua_S,"NetworkMgr");
   tolua_function(tolua_S,"sharedMgr",tolua_MySelf_NetworkMgr_sharedMgr00);
   tolua_function(tolua_S,"ConnectServer",tolua_MySelf_NetworkMgr_ConnectServer00);
   tolua_function(tolua_S,"CloseServer",tolua_MySelf_NetworkMgr_CloseServer00);
   tolua_function(tolua_S,"GetNetworkType",tolua_MySelf_NetworkMgr_GetNetworkType00);
   tolua_function(tolua_S,"UnMarshalIntFromProtocol",tolua_MySelf_NetworkMgr_UnMarshalIntFromProtocol00);
   tolua_function(tolua_S,"MarshalProtocolStart",tolua_MySelf_NetworkMgr_MarshalProtocolStart00);
   tolua_function(tolua_S,"MarshalIntToProtocol",tolua_MySelf_NetworkMgr_MarshalIntToProtocol00);
   tolua_function(tolua_S,"MarshalStringToProtocol",tolua_MySelf_NetworkMgr_MarshalStringToProtocol00);
   tolua_function(tolua_S,"MarshalProtocolEndAndSend",tolua_MySelf_NetworkMgr_MarshalProtocolEndAndSend00);
   tolua_function(tolua_S,"c2s_CmdGameDataSend",tolua_MySelf_NetworkMgr_c2s_CmdGameDataSend00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"aeditor",0);
  tolua_beginmodule(tolua_S,"aeditor");
   tolua_cclass(tolua_S,"AEParamAmmend","aeditor::AEParamAmmend","",NULL);
   tolua_beginmodule(tolua_S,"AEParamAmmend");
    tolua_function(tolua_S,"create",tolua_MySelf_aeditor_AEParamAmmend_create00);
    tolua_function(tolua_S,"AddPos",tolua_MySelf_aeditor_AEParamAmmend_AddPos00);
    tolua_function(tolua_S,"AddSprite",tolua_MySelf_aeditor_AEParamAmmend_AddSprite00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ActionTemplateTable","aeditor::ActionTemplateTable","CCNode",NULL);
   tolua_beginmodule(tolua_S,"ActionTemplateTable");
    tolua_function(tolua_S,"create",tolua_MySelf_aeditor_ActionTemplateTable_create00);
    tolua_function(tolua_S,"RunUIAction",tolua_MySelf_aeditor_ActionTemplateTable_RunUIAction00);
    tolua_function(tolua_S,"RunAeAction",tolua_MySelf_aeditor_ActionTemplateTable_RunAeAction00);
    tolua_function(tolua_S,"RunAeActionWithParam",tolua_MySelf_aeditor_ActionTemplateTable_RunAeActionWithParam00);
    tolua_function(tolua_S,"GetSpriteByName",tolua_MySelf_aeditor_ActionTemplateTable_GetSpriteByName00);
    tolua_function(tolua_S,"RemoveByHandle",tolua_MySelf_aeditor_ActionTemplateTable_RemoveByHandle00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"EVENT_BEGIN",EVENT_BEGIN);
  tolua_constant(tolua_S,"EVENT_UIWIDGET_PUSH_DOWN",EVENT_UIWIDGET_PUSH_DOWN);
  tolua_constant(tolua_S,"EVENT_UIWIDGET_MOVE",EVENT_UIWIDGET_MOVE);
  tolua_constant(tolua_S,"EVENT_UIWIDGET_RELEASE",EVENT_UIWIDGET_RELEASE);
  tolua_constant(tolua_S,"EVENT_END",EVENT_END);
  tolua_cclass(tolua_S,"GFuncMgr","GFuncMgr","",NULL);
  tolua_beginmodule(tolua_S,"GFuncMgr");
   tolua_function(tolua_S,"GetInstance",tolua_MySelf_GFuncMgr_GetInstance00);
   tolua_function(tolua_S,"AddFunc",tolua_MySelf_GFuncMgr_AddFunc00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"csvtable","csvtable","",NULL);
  tolua_beginmodule(tolua_S,"csvtable");
   tolua_function(tolua_S,"Fields",tolua_MySelf_csvtable_Fields00);
   tolua_function(tolua_S,"Rows",tolua_MySelf_csvtable_Rows00);
   tolua_function(tolua_S,"Columns",tolua_MySelf_csvtable_Columns00);
   tolua_function(tolua_S,"GetRecByColName",tolua_MySelf_csvtable_GetRecByColName00);
   tolua_function(tolua_S,"GetRecByColIndex",tolua_MySelf_csvtable_GetRecByColIndex00);
   tolua_function(tolua_S,"GetRecFromIndex",tolua_MySelf_csvtable_GetRecFromIndex00);
   tolua_function(tolua_S,"GetColIndex",tolua_MySelf_csvtable_GetColIndex00);
   tolua_function(tolua_S,"GetRowIndex",tolua_MySelf_csvtable_GetRowIndex00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"InitDataTables",tolua_MySelf_InitDataTables00);
  tolua_function(tolua_S,"GetTable",tolua_MySelf_GetTable00);
  tolua_cclass(tolua_S,"download_param","download_param","CCObject",NULL);
  tolua_beginmodule(tolua_S,"download_param");
   tolua_function(tolua_S,"create",tolua_MySelf_download_param_create00);
   tolua_function(tolua_S,"getRet",tolua_MySelf_download_param_getRet00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"update_param","update_param","CCObject",NULL);
  tolua_beginmodule(tolua_S,"update_param");
   tolua_function(tolua_S,"create",tolua_MySelf_update_param_create00);
   tolua_function(tolua_S,"getRet",tolua_MySelf_update_param_getRet00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AssetsUpdateManager","AssetsUpdateManager","",NULL);
  tolua_beginmodule(tolua_S,"AssetsUpdateManager");
   tolua_function(tolua_S,"GetInstance",tolua_MySelf_AssetsUpdateManager_GetInstance00);
   tolua_function(tolua_S,"CheckUpdate",tolua_MySelf_AssetsUpdateManager_CheckUpdate00);
   tolua_function(tolua_S,"GetDocumentPath",tolua_MySelf_AssetsUpdateManager_GetDocumentPath00);
   tolua_function(tolua_S,"GetTmpPath",tolua_MySelf_AssetsUpdateManager_GetTmpPath00);
   tolua_function(tolua_S,"GetCachePath",tolua_MySelf_AssetsUpdateManager_GetCachePath00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"aStar","aStar","",NULL);
  tolua_beginmodule(tolua_S,"aStar");
   tolua_function(tolua_S,"GetNext",tolua_MySelf_aStar_GetNext00);
   tolua_function(tolua_S,"GetX",tolua_MySelf_aStar_GetX00);
   tolua_function(tolua_S,"GetY",tolua_MySelf_aStar_GetY00);
   tolua_function(tolua_S,"Release",tolua_MySelf_aStar_Release00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GMapMgr","GMapMgr","",NULL);
  tolua_beginmodule(tolua_S,"GMapMgr");
   tolua_function(tolua_S,"GetInstance",tolua_MySelf_GMapMgr_GetInstance00);
   tolua_function(tolua_S,"SetMaxSize",tolua_MySelf_GMapMgr_SetMaxSize00);
   tolua_function(tolua_S,"SetMapGrid",tolua_MySelf_GMapMgr_SetMapGrid00);
   tolua_function(tolua_S,"GetMapGrid",tolua_MySelf_GMapMgr_GetMapGrid00);
   tolua_function(tolua_S,"AStarStart",tolua_MySelf_GMapMgr_AStarStart00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_MySelf (lua_State* tolua_S) {
 return tolua_MySelf_open(tolua_S);
};
#endif

