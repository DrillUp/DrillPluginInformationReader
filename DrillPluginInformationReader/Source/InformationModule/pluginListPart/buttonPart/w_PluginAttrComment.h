#ifndef W_PluginAttrComment_H
#define W_PluginAttrComment_H

#include <QtWidgets/QDialog>
#include "ui_W_PluginAttrComment.h"

/*
-----==========================================================-----
		�ࣺ		����˵������.h
		����ģ�飺	��Ϣģ��
		���ܣ�		����˵�����ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/

class W_PluginAttrComment : public QDialog
{
	Q_OBJECT

	public:
		W_PluginAttrComment(QWidget *parent = 0);		//���캯��
		~W_PluginAttrComment();							//��������
		
		
	//-----------------------------------
	//----����
									//���� - ��������
									//���� - ��ȡ����
									//���� - �������� -> ui����
									//���� - ui���� -> ��������
									//���� - �ύ���ݣ�У�飩
	private:
		Ui::W_PluginAttrComment ui;
		
};

#endif // W_QExpressionTest_H
