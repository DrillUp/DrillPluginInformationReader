#pragma once

#include "Source/PluginModule/scriptReader/s_ScriptAnnotationReader.h"

/*
-----==========================================================-----
		类：		插件详细信息 容器.h
		作者：		drill_up
		所属模块：	交互模块
		功能：		管理指定工程中的全部插件配置数据。
					【封装的容器结构，注意接收读取的信号】
					（详细见.cpp）
-----==========================================================-----
*/
class S_InformationDataContainer : public QObject
{
	Q_OBJECT

	public:
		S_InformationDataContainer();
		~S_InformationDataContainer();
		static S_InformationDataContainer* cur_manager;			//单例
		static S_InformationDataContainer* getInstance();		//单例，获取自己（必须要拿到全局配置才能进行计算）

	//-----------------------------------
	//----数据
	private:
		QList<C_ScriptAnnotation> data_AnnotationTank;
	public:
										//数据 - 获取全部插件数据
										//		【说明】：获取数据前，要确保你之前 手动 执行了read读取，不然获取不到数据。
		QList<C_ScriptAnnotation> getAnnotationTank();
										//数据 - 获取对应的插件数据
										//		【说明】：获取数据前，要确保你之前 手动 执行了read读取，不然获取不到数据。
										//		【说明】：没有则返回空指针。
		C_ScriptAnnotation getAnnotation(QString pluginName);


	//-----------------------------------
	//----读取
	public slots:
										//读取 - 读取全部完整数据（plugins文件夹下所有插件）
		void loadAllAnnotationData();

};
