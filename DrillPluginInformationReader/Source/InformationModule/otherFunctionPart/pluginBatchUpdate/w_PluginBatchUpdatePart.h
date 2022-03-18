#ifndef W_PluginBatchUpdatePart_H
#define W_PluginBatchUpdatePart_H

#include "ui_W_PluginBatchUpdatePart.h"
#include "p_PluginBatchUpdatePart.h"

/*
-----==========================================================-----
		�ࣺ		���²�� ����.h
		���ߣ�		drill_up
		����ģ�飺	��Ϣģ��

		���ܣ�		���²���Ĵ��ڡ�
					����ϸ��cpp��
-----==========================================================-----
*/
class W_PluginBatchUpdatePart : public QDialog
{
	Q_OBJECT

	public:
		W_PluginBatchUpdatePart(QWidget *parent = 0);
		~W_PluginBatchUpdatePart();

	//-----------------------------------
	//----�ؼ�
	protected:
		P_PluginBatchUpdatePart* m_p_PluginBatchUpdatePart;
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
		Ui::W_PluginBatchUpdatePart ui;
};

#endif // W_PluginBatchUpdatePart_H
