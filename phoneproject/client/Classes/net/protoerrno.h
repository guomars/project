
#ifndef __GNET_ERRCODE_H
#define __GNET_ERRCODE_H

namespace GNET
{
	enum ErrCode {
		ERR_SUCCESS = 0,			// 成功
		ERR_TOBECONTINUE = 1,		// 成功，并且还有更多数据未传递完，目前未用

		ERR_INVALID_ACCOUNT = 2,	// 帐号不存在
		ERR_INVALID_PASSWORD = 3,	// 密码错误
		ERR_TIMEOUT = 4,			// 超时
		ERR_INVALID_ARGUMENT = 5,	// 参数错误
		ERR_FRIEND_SYNCHRONIZE = 6,	// 好友信息保存到数据库时无法同步
		ERR_SERVERNOTSUPPLY = 7,	// 该服务器不支持该请求
		ERR_COMMUNICATION=8,		// 网络通讯错误
		ERR_ACCOUNTLOCKED=9,		// 多次重复登陆，当前用户的一个登陆正在被处理，处于锁定状态
		ERR_MULTILOGIN	=10,		// 多次重复登陆，且用户选择自动下线
	};
	
};

#endif



