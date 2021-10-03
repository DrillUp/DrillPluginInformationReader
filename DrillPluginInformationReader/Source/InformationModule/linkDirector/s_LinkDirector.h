#pragma once


/*
-----==========================================================-----
		类：		链接文件引导器.h
		所属模块：	插件模块
		功能：		读取js文件内的所有数据 @的注解 内容。
					（详细见.cpp）
-----==========================================================-----
*/

class S_LinkDirector : public QObject
{
	Q_OBJECT

	public:
		S_LinkDirector();
		~S_LinkDirector();
		static S_LinkDirector* cur_manager;			//单例
		static S_LinkDirector* getInstance();			//单例，获取自己（必须要拿到全局配置才能进行计算）
		
		
	//-----------------------------------
	//----文档路径管理器
	protected:
		QString m_docDir;				//文档路径
	public:
										//数据 - 获取文档路径
		QString getDocDir();
										//路径 - 打开指定路径
		void openLink_Doc(QString text);

	//-----------------------------------
	//----数据
	public:
										//数据 - 获取全部文件夹名称
		QStringList getDataAllDocDirName();

	//-----------------------------------
	//----链接
	public:
										//链接 - 将字符串中的 文档、路径 转为链接
		QString signLink_Docs(QString data);

};
