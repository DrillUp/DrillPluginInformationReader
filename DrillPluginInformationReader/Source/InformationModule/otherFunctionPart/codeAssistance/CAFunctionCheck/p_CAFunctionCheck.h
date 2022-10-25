#ifndef P_CAFunctionCheck_H
#define P_CAFunctionCheck_H

#include <QObject>

/*
-----==========================================================-----
		�ࣺ		����У����.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��
		
		�����ܣ�	�����Զ����Excel����ʽ��
					����ϸ��cpp��
-----==========================================================-----
*/
class P_CAFunctionCheck : public QObject
{
	Q_OBJECT

	public:
		P_CAFunctionCheck(QObject *parent = 0);
		~P_CAFunctionCheck();
		
	//-----------------------------------
	//----������
	public slots: 
								//������ - ���� ���в����д
		QString generate_AllAbbreviation();
								//������ - ���� ���в���̳еķ�����
		QString generate_AllInheritFunctionName();
								//������ - У�����ĺ����̳���
								//		��˵�������̳еĺ�������ȡ���ĺ�������һ�£��ᱻ�г���
		QString generate_WrongInheritFunctionName();
								//������ - У���ظ�����ĺ�����
								//		��˵������ֻҪ"var _drill"�����ظ����֣���ô���г���
		QString generate_RepeatDefinition();

};

#endif // P_CAFunctionCheck_H
