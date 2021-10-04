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
		static S_LinkDirector* getInstance();		//单例，获取自己（必须要拿到全局配置才能进行计算）
		
		
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
										//数据 - 获取可点击的文件夹名称
		QStringList getAllClickableDirName();

	//-----------------------------------
	//----链接
	public:
										//链接 - 将字符串中的 "\n" 替换为"<br>"
										//		【说明】：注意，qt中并不支持"&nbsp"这种字符，直接空格即可。
		QString signBrTag(QString data);
										//链接 - 使用"<p>"包裹字符串
		QString signPTag(QString data);
										//链接 - 将字符串中的 文档、路径 转为"<a>"链接
										//		【说明】：注意，只把"xxx.docx"用"<a>"标签包裹。
		QString signATag_Docs(QString data);

};
