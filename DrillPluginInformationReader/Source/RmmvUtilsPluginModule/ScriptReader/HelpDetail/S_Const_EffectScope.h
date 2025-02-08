#pragma once
#include <QJsonObject>


/*
-----==========================================================-----
		类：		帮助数据-作用域 常量值.h
		作者：		drill_up
		所属模块：	插件模块
		功能：		常量值在这单例中可以直接获取。
					（详细见.cpp）
-----==========================================================-----
*/
class S_Const_EffectScope{

	public:
		S_Const_EffectScope();
		~S_Const_EffectScope();
		static S_Const_EffectScope* cur_instance;		//单例
		static S_Const_EffectScope* getInstance();		//单例，获取自己
		
	//-----------------------------------
	//----界面常量
	protected:
		QList<QString> m_sceneNameList;					//界面名称
		QList<QList<QString>> m_sceneKeyMatrix;			//界面关键字
	public:
									//获取 - 界面名称（全部）
		QStringList getSceneName_All();
									//获取 - 界面名称 - 地图界面
		QString getSceneName_Map();
									//获取 - 界面名称 - 战斗界面
		QString getSceneName_Battle();
									//获取 - 界面名称 - 菜单界面
		QString getSceneName_Menu();
									//获取 - 界面名称 - 其它界面
		QStringList getSceneName_Other();
									//获取 - 界面名称（根据界面关键字）
		QString getSceneName_BySceneKey(QString sceneKey);

									//获取 - 界面关键字（全部）
		QStringList getSceneKey_All();
									//获取 - 界面关键字（根据界面名称）
		QStringList getSceneKey_ByName(QString scene_name);
};
