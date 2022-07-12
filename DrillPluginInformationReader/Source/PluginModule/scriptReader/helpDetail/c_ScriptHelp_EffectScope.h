#pragma once
#include <QList>


/*
-----==========================================================-----
		类：		帮助数据-作用域 数据类.h
		所属模块：	插件模块
		功能：		帮助信息中的数据。
					（详细见.cpp）
-----==========================================================-----
*/
class C_ScriptHelp_EffectScope{

	public:
		C_ScriptHelp_EffectScope();
		~C_ScriptHelp_EffectScope();

	//-----------------------------------
	//----数据
	public:
		QStringList scope_list;		//作用域（地图界面/战斗界面/菜单界面）
		QString comments;			//作用域说明
	public:
							//数据 - 可作用于地图界面
		bool isEnableSceneMap();
							//数据 - 可作用于战斗界面
		bool isEnableSceneBattle();
							//数据 - 可作用于菜单界面
		bool isEnableSceneMenu();
							//数据 - 可作用于界面
		bool isEnableScene(QString scene_name);
							//数据 - 获取作用域
		QStringList getEnabledScene();
							//数据 - 除此三种类型以外的界面
		QStringList getOtherScene();

};
