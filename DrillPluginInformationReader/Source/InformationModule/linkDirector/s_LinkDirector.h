#pragma once


/*
-----==========================================================-----
		�ࣺ		�����ļ�������.h
		����ģ�飺	���ģ��
		���ܣ�		��ȡjs�ļ��ڵ��������� @��ע�� ���ݡ�
					����ϸ��.cpp��
-----==========================================================-----
*/

class S_LinkDirector : public QObject
{
	Q_OBJECT

	public:
		S_LinkDirector();
		~S_LinkDirector();
		static S_LinkDirector* cur_manager;			//����
		static S_LinkDirector* getInstance();		//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		
		
	//-----------------------------------
	//----�ĵ�·��������
	protected:
		QString m_docDir;				//�ĵ�·��
	public:
										//���� - ��ȡ����·��
		QString getProjectDir();
										//���� - ��ȡ�ĵ�·��
		QString getDocDir();
										//·�� - ��ָ���ĵ�·��
		void openLink_Doc(QString text);
										//·�� - ��ָ��ͼƬ·��
		void openLink_Src(QString text);
										//·�� - �򿪲���嵥
		void openLink_specific_pluginListing();

	//-----------------------------------
	//----����
	public:
										//���� - ��ȡ�ɵ�����ļ�������
		QStringList getAllClickableDirName();
										//���� - Ѱ���ĵ�����
										//		��˵�������ĵ����� docx �� xlsx������ǰ����Ҫ�ո�����ţ����ʽ"xxx.docx"�� xxxx xxx.docx��
		QStringList findDocsNameList(QString data);
										//���� - Ѱ�Ҳ������
										//		��˵������������ȫƥ�����еĲ�����ơ�
		QStringList findPluginNameList(QString data);

	//-----------------------------------
	//----����
	public:
										//���� - ���ַ����е� "<" �滻Ϊ"&lt;"��">" �滻Ϊ"&gt;"��
		QString signLtGtTag(QString data);
		void signLtGtTag(QStringList* data);
										//���� - ���ַ����е� "\n" �滻Ϊ"<br>"
										//		��˵������ע�⣬qt�в���֧��"&nbsp"�����ַ���ֱ�ӿո񼴿ɡ�
		QString signBrTag(QString data);
										//���� - ʹ��"<p>"�����ַ���
		QString signPTag(QString data);
										//���� - ���ַ����е� �ĵ����ĵ�·�� תΪ"<a>"����
										//		��˵������ע�⣬��"xxx.docx"��"xxx.xlsx"��"<a>"��ǩ������
		QString signATag_Docs(QString data);
										//���� - �� ��Դ·�� ����"<a>"����
										//		��˵��������"img/xxx"��"<a>"��ǩ������
		QString signATag_Src(QString src_path);
										//���� - ���ַ����е� ������� תΪ"<a>"����
										//		��˵������������ȫƥ�����еĲ�����ƣ�����ת����
		QString signATag_Plugin(QString data);
										//���� - ���ַ����е� "����嵥.xlsx" תΪ"<a>"����
										//		��˵������ֻ��� ����嵥 �ַ�����
		QString signATag_specific_pluginListing(QString data);

};
