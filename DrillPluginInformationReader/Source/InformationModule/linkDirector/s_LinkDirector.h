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
										//���� - ��ȡ�ĵ�·��
		QString getDocDir();
										//·�� - ��ָ��·��
		void openLink_Doc(QString text);

	//-----------------------------------
	//----����
	public:
										//���� - ��ȡ�ɵ�����ļ�������
		QStringList getAllClickableDirName();

	//-----------------------------------
	//----����
	public:
										//���� - ���ַ����е� "\n" �滻Ϊ"<br>"
										//		��˵������ע�⣬qt�в���֧��"&nbsp"�����ַ���ֱ�ӿո񼴿ɡ�
		QString signBrTag(QString data);
										//���� - ʹ��"<p>"�����ַ���
		QString signPTag(QString data);
										//���� - ���ַ����е� �ĵ���·�� תΪ"<a>"����
										//		��˵������ע�⣬ֻ��"xxx.docx"��"<a>"��ǩ������
		QString signATag_Docs(QString data);

};
