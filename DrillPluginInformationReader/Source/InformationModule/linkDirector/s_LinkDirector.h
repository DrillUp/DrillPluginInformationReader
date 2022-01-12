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
										//数据 - 获取工程路径
		QString getProjectDir();
										//数据 - 获取文档路径
		QString getDocDir();
										//路径 - 打开指定文档路径
		void openLink_Doc(QString text);
										//路径 - 打开指定图片路径
		void openLink_Src(QString text);
										//路径 - 打开插件清单
		void openLink_specific_pluginListing();

	//-----------------------------------
	//----数据
	public:
										//数据 - 获取可点击的文件夹名称
		QStringList getAllClickableDirName();
										//数据 - 寻找文档名称
										//		【说明】：文档包括 docx 和 xlsx。名称前面需要空格或引号，如格式"xxx.docx"或 xxxx xxx.docx。
		QStringList findDocsNameList(QString data);
										//数据 - 寻找插件名称
										//		【说明】：必须完全匹配现有的插件名称。
		QStringList findPluginNameList(QString data);

	//-----------------------------------
	//----链接
	public:
										//链接 - 将字符串中的 "<" 替换为"&lt;"，">" 替换为"&gt;"，
		QString signLtGtTag(QString data);
		void signLtGtTag(QStringList* data);
										//链接 - 将字符串中的 "\n" 替换为"<br>"
										//		【说明】：注意，qt中并不支持"&nbsp"这种字符，直接空格即可。
		QString signBrTag(QString data);
										//链接 - 使用"<p>"包裹字符串
		QString signPTag(QString data);
										//链接 - 将字符串中的 文档、文档路径 转为"<a>"链接
										//		【说明】：注意，把"xxx.docx"或"xxx.xlsx"用"<a>"标签包裹。
		QString signATag_Docs(QString data);
										//链接 - 将 资源路径 包裹"<a>"链接
										//		【说明】：把"img/xxx"用"<a>"标签包裹。
		QString signATag_Src(QString src_path);
										//链接 - 将字符串中的 插件名称 转为"<a>"链接
										//		【说明】：必须完全匹配现有的插件名称，才能转换。
		QString signATag_Plugin(QString data);
										//链接 - 将字符串中的 "插件清单.xlsx" 转为"<a>"链接
										//		【说明】：只针对 插件清单 字符串。
		QString signATag_specific_pluginListing(QString data);

};
