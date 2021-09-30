#ifndef W_LoadingTip_H
#define W_LoadingTip_H

#include <QDialog>

/*
-----==========================================================-----
		�ࣺ		�ް�ť������ʾ����.h
		����ģ�飺	����ģ��
		���ܣ�		������ʾ�û����������
-----==========================================================-----
*/
class W_LoadingTip : public QDialog
{
	Q_OBJECT

	public:
		W_LoadingTip(QString text = "������...", QWidget *parent = 0);
		~W_LoadingTip();

	//-----------------------------------
	//----�ؼ�
	public:
		QVBoxLayout* m_layout;
		QLabel* m_label;
	public slots:
							//�ؼ� - �޸��ı�
		void changeText(QString text);
		
	//-----------------------------------
	//----����
	//	���ޣ�

};

#endif // W_LoadingTip_H
