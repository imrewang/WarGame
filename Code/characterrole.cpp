#include "characterrole.h"




Sultan::Sultan(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 290; 
    m_fullhp = 290;

    m_move = m_fullmove = 9;

    m_attrack = 110;
    m_armor = 90;

    m_attrackable = 1;

    m_name = "苏丹亲卫1";

    m_icon.load(WARRIOR_PATH);
    m_icon = m_icon.scaled(CELL_SIZE, CELL_SIZE);
    setPixmap(m_icon);

    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);

    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}

Teutonic::Teutonic(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 280; m_fullhp = 280;

    m_move = m_fullmove = 8;

    m_attrack = 120;
    m_armor = 80;

    m_attrackable = 2;

    m_name = "条顿骑士2";

    m_icon.load(ASSASSIN_PATH);
    m_icon = m_icon.scaled(CELL_SIZE, CELL_SIZE);
    setPixmap(m_icon);

    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);

    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}

Hussars::Hussars(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 270; 
    m_fullhp = 270;

    m_move = m_fullmove = 7;

    m_attrack = 130;
    m_armor = 70;
    m_attrackable = 3;

    m_name = "翼骑兵3";

    m_icon.load(SHOOTER_PATH);
    m_icon = m_icon.scaled(CELL_SIZE, CELL_SIZE);
    setPixmap(m_icon);

    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}


Dragoon::Dragoon(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 260; m_fullhp = 260;

    m_move = m_fullmove = 6;

    m_attrack = 140;
    m_armor = 60;

    m_attrackable = 4;

    m_name = "龙骑兵4";

    m_icon.load(MASTER_PATH);
    m_icon = m_icon.scaled(CELL_SIZE, CELL_SIZE);
    setPixmap(m_icon);

    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);

    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}


Mamluk::Mamluk(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 250; m_fullhp = 250;

    m_move = m_fullmove = 5;

    m_attrack = 150;

    m_armor = 50;
    m_attrackable = 5;

    m_name = "马穆鲁克5";

    m_icon.load(TANK_PATH);
    m_icon = m_icon.scaled(CELL_SIZE, CELL_SIZE);
    setPixmap(m_icon);

    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}