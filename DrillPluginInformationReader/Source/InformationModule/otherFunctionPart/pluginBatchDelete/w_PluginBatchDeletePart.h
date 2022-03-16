#ifndef W_PluginBatchDeletePart_H
#define W_PluginBatchDeletePart_H

#include "ui_W_PluginBatchDeletePart.h"
#include "p_PluginBatchDeletePart.h"

/*
-----==========================================================-----
		�ࣺ		������ ����.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		���ܣ�		�������Ĵ��ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/
class W_PluginBatchDeletePart : public QDialog
{
	Q_OBJECT

	public:
		W_PluginBatchDeletePart(QWidget *parent = 0);
		~W_PluginBatchDeletePart();

	//-----------------------------------
	//----�ؼ�
	protected:
		P_PluginBatchDeletePart* m_p_PluginBatchDeletePart;
	public:

	//-----------------------------------
	//----����
	public:
										//���� - �������� -> ui����
		void putDataToUi();							
										//���� - ui���� -> ��������
		void putUiToData();

	public slots:
										//���� - �ύ���ݣ�У�飩
		void acceptData();	
	signals:
		void acceptDataSignal(QString data);

	private:
		Ui::W_PluginBatchDeletePart ui;
};

#endif // W_PluginBatchDeletePart_H
