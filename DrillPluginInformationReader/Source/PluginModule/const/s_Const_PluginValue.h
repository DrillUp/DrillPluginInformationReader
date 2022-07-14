#pragma once
#include <QJsonObject>


/*
-----==========================================================-----
		类：		插件 常量值.h
		版本：		v1.00
		作者：		drill_up
		所属模块：	工具模块
		功能：		所有常量值在这里直接获取。
					（详细见.cpp）
-----==========================================================-----
*/
class S_Const_PluginValue{

	public:
		S_Const_PluginValue();
		~S_Const_PluginValue();
		static S_Const_PluginValue* cur_instance;		//单例
		static S_Const_PluginValue* getInstance();		//单例，获取自己（必须要拿到全局配置才能进行计算）
		
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
