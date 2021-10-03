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
		static S_LinkDirector* getInstance();			//��������ȡ�Լ�������Ҫ�õ�ȫ�����ò��ܽ��м��㣩
		
		
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
										//���� - ��ȡȫ���ļ�������
		QStringList getDataAllDocDirName();

	//-----------------------------------
	//----����
	public:
										//���� - ���ַ����е� �ĵ���·�� תΪ����
		QString signLink_Docs(QString data);

};
