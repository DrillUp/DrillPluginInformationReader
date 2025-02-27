#include "stdafx.h"
#include "p_ScriptHelp_Command.h"

#include "Source/InformationModule/linkDirector/s_LinkDirector.h"
#include "Source/Utils/Common/TTool.h"

/*
-----==========================================================-----
		类：		指令 控件块.cpp
		作者：		drill_up
		所属模块：	信息模块

		主功能：	显示控件信息的结构。
-----==========================================================-----
*/
P_ScriptHelp_Command::P_ScriptHelp_Command(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//-----------------------------------
	//----控件初始化
	this->setData(nullptr);		//（初始没有任何数据）

	//-----------------------------------
	//----事件绑定
	//（无）

}

P_ScriptHelp_Command::~P_ScriptHelp_Command(){
}

/*-------------------------------------------------
		控件 - 清空全部子控件
*/
void P_ScriptHelp_Command::clearAllChild(){

	// > 断开连接
	for (int i = this->m_labelTank.count()-1; i >=0; i--){
		QLabel* label = this->m_labelTank.at(i);
		if (label == nullptr){continue;}
		disconnect(label);
	}
	this->m_labelTank.clear();
	for (int i = this->m_btnTank.count() - 1; i >= 0; i--){
		QToolButton* btn = this->m_btnTank.at(i);
		if (btn == nullptr){ continue; }
		disconnect(btn);
	}
	this->m_btnTank.clear();

	// > 删除下面的全部控件
	QLayout* layout = this->layout();
	QLayoutItem *child;
	while ((child = layout->takeAt(0)) != 0){
		child->widget()->deleteLater();
	}
}
/*-------------------------------------------------
		控件 - 链接被点击
*/
void P_ScriptHelp_Command::linkClicked_docs(QString data){
	S_LinkDirector::getInstance()->openLink_Doc(data);
}
/*-------------------------------------------------
		控件 - 复制按钮被点击
*/
void P_ScriptHelp_Command::copyBtnClicked(){
	QToolButton* cur_btn = qobject_cast<QToolButton*>(sender());
	QString command = cur_btn->statusTip();

	QClipboard *board = QApplication::clipboard();
	board->clear();
	board->setText(command, QClipboard::Clipboard);
}

/*-------------------------------------------------
		块 - 设置数据
*/
void P_ScriptHelp_Command::setData(C_ScriptHelp_Command* data){
	this->clearAllChild();

	// > 全为空情况
	if (data == nullptr || data->isNull()){
		QLabel* label = new QLabel("插件没有任何指令说明。");
		label->setAlignment(Qt::AlignCenter);
		this->layout()->addWidget(label);
		return;
	}

	// > 指令组 底板控件
	QList<C_ScriptHelp_CommandGroup> c_group_list = data->getGroupList();
	for (int i = 0; i < c_group_list.count(); i++){
		C_ScriptHelp_CommandGroup c_group = c_group_list.at(i);
		QGroupBox* group = new QGroupBox(this);
		QGridLayout* layout = new QGridLayout(group);
		layout->setSpacing(2);
		layout->setColumnStretch(1, 1);
		group->setTitle(c_group.getGroupFullName());
		group->setLayout(layout);
		int cur_row = 0;

		// > 指令全文
		QStringList tag_list = c_group.getGrid_TagList();
		QStringList command_list = c_group.getGrid_CommandList();
		QStringList note_list = c_group.getGrid_NoteList();
		for (int j = 0; j < tag_list.count(); j++){
			QString tag = tag_list.at(j);
			QString command = command_list.at(j);
			QString note = note_list.at(j);

			// > 指令 - 标签头
			QLabel* label_tag = new QLabel(tag, group);
			label_tag->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
			layout->addWidget(label_tag, cur_row, 0, 1, 1);
			this->m_labelTank.append(label_tag);
			
			// > 指令 - 标签头 - 颜色区分
			this->refreshLabelStyle(label_tag);

			// > 指令 - 单行指令
			if (command != ""){
				command = command.replace("<", "&lt;");
				QLabel* label_command = new QLabel(command, group);
				label_command->setWordWrap(true);
				label_command->setTextInteractionFlags(label_command->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
				label_command->setCursor(QCursor(Qt::IBeamCursor));			//（设置文本可圈选，且文本光标变化）
				label_command->setStyleSheet("background-color: rgb(255, 255, 255);");
				layout->addWidget(label_command, cur_row, 1, 1, 1);
				this->m_labelTank.append(label_command);

				// > 指令 - 单行指令 - 复制按钮
				QString copy_command = command.trimmed();
				if (copy_command.mid(0, 1) == ">" ||
					copy_command.mid(0, 1) == "<" ||
					copy_command.mid(0, 1) == "=" ||
					copy_command.mid(0, 1) == "\\"){
					QToolButton* btn_copy = new QToolButton(group);
					btn_copy->setText("复制指令");
					btn_copy->setToolTip("复制指令");
					btn_copy->setIcon(QIcon(QRC_IconSrcPath + "/menu/Common_Paste.png"));
					btn_copy->setIconSize(QSize(14,14));
					btn_copy->setStatusTip(copy_command);
					btn_copy->setToolButtonStyle(Qt::ToolButtonIconOnly);
					connect(btn_copy, &QToolButton::clicked, this, &P_ScriptHelp_Command::copyBtnClicked);
					layout->addWidget(btn_copy, cur_row, 2, 1, 1);
					this->m_btnTank.append(btn_copy);
				}
			}
			cur_row += 1;

			// > 附加注释情况
			if (note != ""){
				QLabel* label_note = new QLabel(note, group);
				label_note->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
				label_note->setWordWrap(true);
				layout->addWidget(label_note, cur_row, 1, 1, 1);
				this->m_labelTank.append(label_note);
			}
			cur_row += 1;
		}

		// > 空行
		QWidget* widget_empty = new QWidget(group);
		widget_empty->setMinimumHeight(10);
		layout->addWidget(widget_empty, cur_row, 0, 1, 3);
		cur_row += 1;

		// > 说明内容
		QStringList data_list = c_group.context_note;
		for (int j = 0; j < data_list.count(); j++){
			QString temp_data = data_list.at(j);
			temp_data = "◆ " + temp_data;

			temp_data = S_LinkDirector::getInstance()->signATag_Docs(temp_data);
			temp_data = S_LinkDirector::getInstance()->signBrTag(temp_data);
			temp_data = S_LinkDirector::getInstance()->signPTag(temp_data);
			QLabel* label = new QLabel(temp_data, group);
			label->setWordWrap(true);
			label->setTextInteractionFlags(label->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
			label->setCursor(QCursor(Qt::IBeamCursor));
			layout->addWidget(label, cur_row, 0, 1, 3);
			this->m_labelTank.append(label);
			connect(label, &QLabel::linkActivated, this, &P_ScriptHelp_Command::linkClicked_docs);
			cur_row += 1;
		}

		// > 旧指令全文
		QStringList tag_list_old = c_group.getGrid_OldTagList();
		QStringList command_list_old = c_group.getGrid_OldCommandList();
		for (int j = 0; j < tag_list_old.count(); j++){
			QString tag = tag_list_old.at(j);
			QString command = command_list_old.at(j);

			// > 指令 - 标签头
			QLabel* label_tag = new QLabel(tag, group);
			label_tag->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
			layout->addWidget(label_tag, cur_row, 0, 1, 1);
			this->m_labelTank.append(label_tag);

			// > 指令 - 标签头 - 颜色区分
			this->refreshLabelStyle(label_tag);

			// > 指令 - 单行指令
			if (command != ""){
				QLabel* label_command = new QLabel(command, group);
				label_command->setWordWrap(true);
				label_command->setTextInteractionFlags(label_command->textInteractionFlags() | Qt::TextInteractionFlag::TextSelectableByMouse);
				label_command->setCursor(QCursor(Qt::IBeamCursor));			//（设置文本可圈选，且文本光标变化）
				label_command->setStyleSheet("background-color: rgb(255, 255, 255);");
				layout->addWidget(label_command, cur_row, 1, 1, 1);
				this->m_labelTank.append(label_command);

				// > 指令 - 单行指令 - 复制按钮
				QString copy_command = command.trimmed();
				if (copy_command.mid(0, 1) == ">" ||
					copy_command.mid(0, 1) == "<" ||
					copy_command.mid(0, 1) == "=" ||
					copy_command.mid(0, 1) == "\\"){
					QToolButton* btn_copy = new QToolButton(group);
					btn_copy->setText("复制指令");
					btn_copy->setToolTip("复制指令");
					btn_copy->setIcon(QIcon(QRC_IconSrcPath + "/menu/Common_Paste.png"));
					btn_copy->setIconSize(QSize(14, 14));
					btn_copy->setStatusTip(copy_command);
					btn_copy->setToolButtonStyle(Qt::ToolButtonIconOnly);
					connect(btn_copy, &QToolButton::clicked, this, &P_ScriptHelp_Command::copyBtnClicked);
					layout->addWidget(btn_copy, cur_row, 2, 1, 1);
					this->m_btnTank.append(btn_copy);
				}
			}

			cur_row += 1;
		}


		this->layout()->addWidget(group);
	}
}
/*-------------------------------------------------
		控件 - 刷新颜色（根据指令类型）
*/
void P_ScriptHelp_Command::refreshLabelStyle(QLabel* label){
	QString name = label->text();
	if (name.contains("插件指令(旧)") || name.contains("事件注释(旧)")){
		label->setStyleSheet("color:#989898;font-weight:bold;");
		return;
	}
	if (name.contains("插件指令")){
		label->setStyleSheet("color:#449ed4;font-weight:bold;");
		return;
	}
	if (name.contains("事件注释")){
		label->setStyleSheet("color:#44c49e;font-weight:bold;");
		return;
	}
	if (name.contains("地图备注")){
		label->setStyleSheet("color:#008000;font-weight:bold;");
		return;
	}
	if (name.contains("角色注释") || name.contains("敌人注释") || name.contains("状态注释") || name.contains("技能注释") ){
		label->setStyleSheet("color:#FF7F27;font-weight:bold;");
		return;
	}
	if (name.contains("物品注释") || name.contains("武器注释") || name.contains("护甲注释") || name.contains("移动路线指令") || name.contains("窗口字符")){
		label->setStyleSheet("color:#d4449e;font-weight:bold;");
		return;
	}
}
/*-------------------------------------------------
		块 - 本地数据 -> ui数据
*/
void P_ScriptHelp_Command::putDataToUi(){
	//（暂无）
}
/*-------------------------------------------------
		块 - ui数据 -> 本地数据
*/
void P_ScriptHelp_Command::putUiToData(){
	//（暂无）
}