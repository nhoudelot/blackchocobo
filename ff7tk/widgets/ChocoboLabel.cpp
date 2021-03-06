/****************************************************************************/
//    copyright 2013 -2016  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "ChocoboLabel.h"
// Pull in Icons, Be Sure Paths Are Correct

bool ChocoboLabel::event(QEvent *ev)
{
	if (ev->type()==QEvent::MouseButtonPress && isEnabled){emit(clicked());return true;}
	else{return false;}
}
ChocoboLabel::ChocoboLabel(qreal Scale,QString titleText,bool occupied,QWidget *parent) :
	QWidget(parent)
{
	scale = Scale;
	lblType = new QLabel("");
	lblType->setFixedSize(48*scale,48*scale);

	lblName = new QLabel("");
	lblSex = new QLabel("");
	lblRank = new QLabel("");

	chkOccupied = new QCheckBox();
	chkOccupied->setText(titleText);
	chkOccupied->setMaximumHeight(20*scale);
	chkOccupied->setProperty("HoverStyled",QVariant(true));

	btnCopy = new QPushButton();
	btnCopy->setFlat(true);
	btnCopy->setFixedSize(20*scale,20*scale);
	btnCopy->setIconSize(QSize(16*scale,16*scale));
	btnCopy->setToolTip(QString(tr("Copy")));
	btnCopy->setProperty("HoverStyled",QVariant(true));
	btnCopy->setIcon(QIcon::fromTheme(QString("edit-copy"),QPixmap(":/common/edit-copy")));

	btnPaste = new QPushButton();
	btnPaste->setFlat(true);
	btnPaste->setFixedSize(20*scale,20*scale);
	btnPaste->setIconSize(QSize(16*scale,16*scale));
	btnPaste->setToolTip(QString(tr("Paste")));
	btnPaste->setProperty("HoverStyled",QVariant(true));
	btnPaste->setIcon(QIcon::fromTheme(QString("edit-paste"),QPixmap(":/common/edit-paste")));

	btnRemove = new QPushButton();
	btnRemove->setFlat(true);
	btnRemove->setFixedSize(20*scale,20*scale);
	btnRemove->setIconSize(QSize(16*scale,16*scale));
	btnRemove->setToolTip(QString(tr("Remove")));
	btnRemove->setProperty("HoverStyled",QVariant(true));
	btnRemove->setIcon(QIcon::fromTheme(QString("edit-clear"),QPixmap(":/common/edit-clear")));

    setFontSize(14);
	chkOccupied->setChecked(occupied);

	QHBoxLayout *btnLayout = new QHBoxLayout;
	btnLayout->setContentsMargins(0,0,0,0);
	btnLayout->addWidget(chkOccupied);
	btnLayout->addWidget(btnCopy);
	btnLayout->addWidget(btnPaste);
	btnLayout->addWidget(btnRemove);
	btnLayout->setSpacing(1);

	QHBoxLayout *LeftTopLayout = new QHBoxLayout;
	LeftTopLayout->setContentsMargins(0,0,0,0);
	LeftTopLayout->addWidget(lblName);
	LeftTopLayout->addWidget(lblSex);
	LeftTopLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred));
	LeftTopLayout->setSpacing(1);

	QHBoxLayout *RightTopLayout = new QHBoxLayout;
	RightTopLayout->setContentsMargins(0,0,0,0);
	RightTopLayout->addWidget(lblRank);
	RightTopLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred));
	RightTopLayout->setSpacing(1);

	QVBoxLayout *rightSideLayout = new QVBoxLayout;
	rightSideLayout->setContentsMargins(0,0,0,0);
	rightSideLayout->addLayout(LeftTopLayout);
	rightSideLayout->addLayout(RightTopLayout);

	QHBoxLayout *innerFrameLayout = new QHBoxLayout;
	innerFrameLayout->addWidget(lblType);
	innerFrameLayout->addLayout(rightSideLayout);

	innerFrame = new QFrame;
	innerFrame->setLayout(innerFrameLayout);
	innerFrame->setProperty("HoverStyled",QVariant(true));

	QVBoxLayout *outerFrameLayout = new QVBoxLayout;
	outerFrameLayout->setContentsMargins(3,3,3,3);
	outerFrameLayout->addLayout(btnLayout);
	outerFrameLayout->addWidget(innerFrame);

	outerFrame = new QFrame;
	outerFrame->setLayout(outerFrameLayout);

	QVBoxLayout *finalLayout= new QVBoxLayout;
	finalLayout->setContentsMargins(0,0,0,0);
	finalLayout->addWidget(outerFrame);

	this->setLayout(finalLayout);
	this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	enable(occupied);
	connect(chkOccupied,SIGNAL(toggled(bool)),this,SLOT(chkOccupiedToggled(bool)));
	connect(btnCopy,SIGNAL(clicked()),this,SLOT(copyPushed()));
	connect(btnPaste,SIGNAL(clicked()),this,SLOT(pastePushed()));
	connect(btnRemove,SIGNAL(clicked()),this,SLOT(removePushed()));
}

void ChocoboLabel::setType(int type)
{
	switch(type)
	{
		case 0: lblType->setPixmap(QPixmap("://chocobo/yellow").scaled(lblType->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)); break;
		case 1: lblType->setPixmap(QPixmap("://chocobo/green").scaled(lblType->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)); break;
		case 2: lblType->setPixmap(QPixmap("://chocobo/blue").scaled(lblType->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)); break;
		case 3: lblType->setPixmap(QPixmap("://chocobo/black").scaled(lblType->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)); break;
		case 4: lblType->setPixmap(QPixmap("://chocobo/gold").scaled(lblType->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)); break;
		default: lblType->setPixmap(QPixmap("")); break;
	}
}

void ChocoboLabel::setTitle(QString title){chkOccupied->setText(title);}

void ChocoboLabel::setName(QString decodedName){lblName->setText(decodedName.mid(0,6));/*only space for 6 chars*/}

void ChocoboLabel::setSex(bool male)
{
	if(male){lblSex->setText(QString::fromUtf8("♂"));}
	else{lblSex->setText(QString::fromUtf8("♀"));}
}

void ChocoboLabel::setSex(int sex)
{
	if (sex==0){lblSex->setText(QString::fromUtf8("♂"));}
	else if(sex==1){lblSex->setText(QString::fromUtf8("♀"));}
	else{lblSex->setText("");}
}

void ChocoboLabel::setRank(int wins)
{
	if(wins<0){lblRank->setText("");}
	else if(wins<3){lblRank->setText(tr("Rank:C"));}
	else if(wins<6){lblRank->setText(tr("Rank:B"));}
	else if(wins<9){lblRank->setText(tr("Rank:A"));}
	else{lblRank->setText(tr("Rank:S"));}
}

void ChocoboLabel::setOccupied(bool occupied)
{
	chkOccupied->blockSignals(true);
	chkOccupied->setChecked(occupied);
	chkOccupied->blockSignals(false);
	enable(occupied);
}

void ChocoboLabel::chkOccupiedToggled(bool occupied)
{
	emit occupiedToggled(occupied);
	enable(occupied);
}

void ChocoboLabel::copyPushed(void){emit copy();}

void ChocoboLabel::pastePushed(void){emit paste();}

void ChocoboLabel::removePushed(void)
{
	emit remove();
	clearLabel();
	chkOccupied->setChecked(false);
}

void ChocoboLabel::clearLabel()
{
	setType(-1);
	setRank(-1);
	setName("");
	setSex(-1);
}

void ChocoboLabel::setFontSize(int fontSize)
{
	QString fontStyle =QString("font-size:%1pt;background-color:rgba(0,0,0,0);").arg(fontSize);
	lblName->setStyleSheet(fontStyle);
	lblSex->setStyleSheet(fontStyle);
	lblRank->setStyleSheet(fontStyle);
	lblType->setStyleSheet(fontStyle);
}

void ChocoboLabel::enable(bool enabled)
{
	isEnabled=enabled;
	innerFrame->setEnabled(enabled);
	if(!enabled){setSelected(false);}
}

void ChocoboLabel::setSelected(bool selected)
{
	if(selected){outerFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);innerFrame->setStyleSheet(SelectedBkStyle);}
	else
	{
		outerFrame->setFrameStyle(QFrame::NoFrame);
		QString Style=SelectedBkStyle;
		Style.append(Style.insert(Style.lastIndexOf("]")+1,":enabled:hover"));
		Style.prepend("QWidget[HoverStyled=\"true\"]{background-color:rgba(0,0,0,0);}");
		innerFrame->setStyleSheet(Style);
	}
}

bool ChocoboLabel::isOccupied(void){return chkOccupied->isChecked();}

void ChocoboLabel::setCheckBoxStyle(QString styleSheet){chkOccupied->setStyleSheet(styleSheet);}

void ChocoboLabel::setHoverColorStyle(QString backgroundColor)
{
	SelectedBkStyle=backgroundColor;
	SelectedBkStyle.prepend("QWidget[HoverStyled=\"true\"]{background-color:");
	SelectedBkStyle.append("}");

	backgroundColor.prepend("QPushButton:enabled{background-color:rgba(0,0,0,0);border:0px solid;} QWidget[HoverStyled=\"true\"]:enabled:hover{background-color:");
	backgroundColor.append("}");
	this->setStyleSheet(backgroundColor);
}
