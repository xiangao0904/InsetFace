//---------------------------------------------------------------------------
//
//   MQWidget
//
//          Copyright(C) 1999-2023, tetraface Inc.
//
//	   A class for accessing widgets to construct a graphical user interfaces 
//    such as buttons, check boxes, dialogs and so on.
//
//    　ボタン、チェックボックスやダイアログなどのGUIを構築するためのウィ
//    ジェットにアクセスするクラスです。
//
//---------------------------------------------------------------------------

#ifdef _WIN32
#include <windows.h>
#endif
#include <map>
#include <assert.h>
#include "MQPlugin.h"
#include "MQBasePlugin.h"
#include "MQWidget.h"

static void *ExtractEventOption(void *option, const char *name);
//static BOOL ExtractEventOptionBool(void *option, const char *name, BOOL defval);
static int ExtractEventOptionInt(void *option, const char *name, int defval);
static float ExtractEventOptionFloat(void *option, const char *name, float defval);


static std::map<int, MQWidgetBase*> s_WidgetIDMap;

//---------------------------------------------------------------------------
//  class MQWidgetBase
//---------------------------------------------------------------------------
MQWidgetBase::MQWidgetBase()
{
	m_ID = NullID;
	m_IDOwner = false;
}

MQWidgetBase::MQWidgetBase(int id)
{
	m_ID = id;
	m_IDOwner = false;

	RegisterID();
}

MQWidgetBase::~MQWidgetBase()
{
	if(m_ID != NullID){
		s_WidgetIDMap.erase(m_ID);

		if(m_IDOwner){
			void *ptr[1];
			ptr[0] = NULL;
			MQWidget_Value(m_ID, MQWIDGET_DELETE, (void*)ptr);
		}

		m_ID = NullID;
		m_IDOwner = false;
	}
}

void MQWidgetBase::RegisterID()
{
	if(m_ID != NullID){
		s_WidgetIDMap.insert(std::pair<int,MQWidgetBase*>(m_ID, this));
	}
}

int MQWidgetBase::GetID() const
{
	return m_ID;
}

int MQWidgetBase::AddChild(MQWidgetBase *child)
{
	if(child == NULL) return -1;

	void *ptr[5];
	int child_id = child->GetID();
	int result = -1;

	ptr[0] = (void*)"child";
	ptr[1] = &child_id;
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_ADD_CHILD, (void*)ptr);
	
	return result;
}

int MQWidgetBase::InsertChild(MQWidgetBase *child, int index)
{
	if(child == NULL) return -1;

	void *ptr[7];
	int child_id = child->GetID();
	int result = -1;

	ptr[0] = (void*)"child";
	ptr[1] = &child_id;
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = (void*)"index";
	ptr[5] = &index;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_ADD_CHILD, (void*)ptr);

	return result;
}

void MQWidgetBase::RemoveChild(MQWidgetBase *child)
{
	if(child == NULL) return;

	void *ptr[3];
	int child_id = child->GetID();

	ptr[0] = (void*)"child";
	ptr[1] = &child_id;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_REMOVE_CHILD, (void*)ptr);
}

int MQWidgetBase::GetIndexOfChild(MQWidgetBase *child)
{
	if(child == NULL) return -1;
	
	void *ptr[7];
	int child_id = child->GetID();
	int result = -1;

	ptr[0] = (void*)"indexofchild";
	ptr[1] = NULL;
	ptr[2] = (void*)"child";
	ptr[3] = &child_id;
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

std::wstring MQWidgetBase::GetName()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"name.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"name";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQWidgetBase::SetName(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"name";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

__int64 MQWidgetBase::GetTag()
{
	__int64 value = 0;
	void *ptr[3];
	ptr[0] = (void*)"tag";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetTag(__int64 value)
{
	void *ptr[3];
	ptr[0] = (void*)"tag";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWidgetBase::GetEnabled()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enabled";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetEnabled(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enabled";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWidgetBase::GetVisible()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"visible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

void MQWidgetBase::SetVisible(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"visible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQWidgetBase::LAYOUT_TYPE MQWidgetBase::GetHorzLayout()
{
	char *layout_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"horzlayout";
	ptr[1] = &layout_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(layout_str, "auto") == 0) return LAYOUT_AUTO;
	if(strcmp(layout_str, "fixed") == 0) return LAYOUT_FIXED;
	if(strcmp(layout_str, "hintsize") == 0) return LAYOUT_HINTSIZE;
	if(strcmp(layout_str, "fill") == 0) return LAYOUT_FILL;
	if(strcmp(layout_str, "free") == 0) return LAYOUT_FREE;
	return LAYOUT_AUTO;
}

void MQWidgetBase::SetHorzLayout(LAYOUT_TYPE value)
{
	void *ptr[3];
	ptr[0] = (void*)"horzlayout";
	switch(value){
	default:
	case LAYOUT_AUTO: ptr[1] = (void*)"auto"; break;
	case LAYOUT_FIXED: ptr[1] = (void*)"fixed"; break;
	case LAYOUT_HINTSIZE: ptr[1] = (void*)"hintsize"; break;
	case LAYOUT_FILL: ptr[1] = (void*)"fill"; break;
	case LAYOUT_FREE: ptr[1] = (void*)"free"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQWidgetBase::LAYOUT_TYPE MQWidgetBase::GetVertLayout()
{
	char *layout_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"vertlayout";
	ptr[1] = &layout_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(layout_str, "auto") == 0) return LAYOUT_AUTO;
	if(strcmp(layout_str, "fixed") == 0) return LAYOUT_FIXED;
	if(strcmp(layout_str, "hintsize") == 0) return LAYOUT_HINTSIZE;
	if(strcmp(layout_str, "fill") == 0) return LAYOUT_FILL;
	if(strcmp(layout_str, "free") == 0) return LAYOUT_FREE;
	return LAYOUT_AUTO;
}

void MQWidgetBase::SetVertLayout(LAYOUT_TYPE value)
{
	void *ptr[3];
	ptr[0] = (void*)"vertlayout";
	switch(value){
	default:
	case LAYOUT_AUTO: ptr[1] = (void*)"auto"; break;
	case LAYOUT_FIXED: ptr[1] = (void*)"fixed"; break;
	case LAYOUT_HINTSIZE: ptr[1] = (void*)"hintsize"; break;
	case LAYOUT_FILL: ptr[1] = (void*)"fill"; break;
	case LAYOUT_FREE: ptr[1] = (void*)"free"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQWidgetBase::GetWidth()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"width";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetWidth(int value)
{
#ifdef _DEBUG
	assert(dynamic_cast<MQWindowBase*>(this) != NULL || GetHorzLayout() == LAYOUT_FIXED);
#endif

	void *ptr[3];
	ptr[0] = (void*)"width";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQWidgetBase::GetHeight()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"height";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetHeight(int value)
{
#ifdef _DEBUG
	assert(dynamic_cast<MQWindowBase*>(this) != NULL || GetVertLayout() == LAYOUT_FIXED);
#endif

	void *ptr[3];
	ptr[0] = (void*)"height";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetFillRateX()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"fillrate_x";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetFillRateX(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fillrate_x";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetFillRateY()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"fillrate_y";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetFillRateY(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fillrate_y";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetFillBeforeRate()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"fillbeforerate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetFillBeforeRate(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fillbeforerate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetFillAfterRate()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"fillafterrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetFillAfterRate(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fillafterrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetInSpace()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"inspace";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetInSpace(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"inspace";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetOutSpace()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"outspace";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetOutSpace(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"outspace";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetHintSizeRateX()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"hintsizeratex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetHintSizeRateX(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"hintsizeratex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQWidgetBase::GetHintSizeRateY()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"hintsizeratey";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetHintSizeRateY(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"hintsizeratey";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQWidgetBase::GetCellColumn()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"cellcolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWidgetBase::SetCellColumn(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"cellcolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQWidgetBase::GetHintText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"hinttext.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"hinttext";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQWidgetBase::SetHintText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"hinttext";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQWidgetBase::SetCursor(HCURSOR cursor)
{
	void *ptr[3];
	ptr[0] = (void*)"cursor";
	ptr[1] = (void*)cursor;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

POINT MQWidgetBase::GetJustSize(int max_width, int max_height)
{
	int values[4] = {0, 0, max_width, max_height};
	void *ptr[3];
	ptr[0] = (void*)"justsize";
	ptr[1] = values;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	POINT pt;
	pt.x = values[0];
	pt.y = values[1];
	return pt;
}

bool MQWidgetBase::ClientToScreen(int client_x, int client_y, int *screen_x, int *screen_y)
{
	bool result = false;
	void *ptr[13];
	ptr[0] = (void*)"clienttoscreen";
	ptr[1] = NULL;
	ptr[2] = (void*)"client_x";
	ptr[3] = &client_x;
	ptr[4] = (void*)"client_y";
	ptr[5] = &client_y;
	ptr[6] = (void*)"screen_x";
	ptr[7] = screen_x;
	ptr[8] = (void*)"screen_y";
	ptr[9] = screen_y;
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	return result;
}

bool MQWidgetBase::ScreenToClient(int screen_x, int screen_y, int *client_x, int *client_y)
{
	bool result = false;
	void *ptr[13];
	ptr[0] = (void*)"screentoclient";
	ptr[1] = NULL;
	ptr[2] = (void*)"screen_x";
	ptr[3] = &screen_x;
	ptr[4] = (void*)"screen_y";
	ptr[5] = &screen_y;
	ptr[6] = (void*)"client_x";
	ptr[7] = client_x;
	ptr[8] = (void*)"client_y";
	ptr[9] = client_y;
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	return result;
}

bool MQWidgetBase::ClientToClient(int client_x, int client_y, MQWidgetBase *target, int *target_x, int *target_y)
{
	if(target == NULL){
		*target_x = client_x;
		*target_y = client_y;
		return false;
	}

	int target_id = target->GetID();
	bool result = false;
	void *ptr[15];
	ptr[0] = (void*)"clienttoclient";
	ptr[1] = NULL;
	ptr[2] = (void*)"client_x";
	ptr[3] = &client_x;
	ptr[4] = (void*)"client_y";
	ptr[5] = &client_y;
	ptr[6] = (void*)"target";
	ptr[7] = &target_id;
	ptr[8] = (void*)"target_x";
	ptr[9] = target_x;
	ptr[10] = (void*)"target_y";
	ptr[11] = target_y;
	ptr[12] = (void*)"result";
	ptr[13] = &result;
	ptr[14] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	return result;
}

void MQWidgetBase::Repaint(bool immediate)
{
	void *ptr[5];
	ptr[0] = (void*)"repaint";
	ptr[1] = NULL;
	ptr[2] = (void*)"immediate";
	ptr[3] = &immediate;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQWidgetBase::RefreshPaint()
{
	void *ptr[3];
	ptr[0] = (void*)"refreshpaint";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQWidgetBase::CaptureMouse(bool value)
{
	void *ptr[5];
	ptr[0] = (void*)"capturemouse";
	ptr[1] = NULL;
	ptr[2] = (void*)"value";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

bool MQWidgetBase::CanReceiveMouseEvent()
{
	bool result = false;
	void *ptr[5];
	ptr[0] = (void*)"canreceivemouseevent";
	ptr[1] = NULL;
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

MQWidgetBase *MQWidgetBase::FindWidgetByID(int id)
{
	std::map<int, MQWidgetBase*>::iterator it = s_WidgetIDMap.find(id);
	if(it != s_WidgetIDMap.end()){
		return (*it).second;
	}
	return NULL;
}

int MQWidgetBase::GetSystemWidgetID(MQSystemWidget::WidgetType type)
{
	void *ptr[5];
	int result = -1;

	ptr[0] = (void*)"system";
	switch(type){
	case MQSystemWidget::MainWindow: ptr[1] = (void*)"main_window"; break;
	case MQSystemWidget::OptionPanel: ptr[1] = (void*)"option_panel"; break;
	default: return NullID;
	}
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_FIND, (void*)ptr);
	
	return result;
}

int MQWidgetBase::GetBaseRateSize(double rate)
{
	int result = 0;
	void *ptr[5];
	ptr[0] = (void*)"baseratesize";
	ptr[1] = &rate;
	ptr[2] = (void*)"baseratesize.result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	return result;
}

void MQWidgetBase::GetDefaultFrameColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultframecolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultBackColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultbackcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultTextColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaulttextcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultTitleBackColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaulttitlebackcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultTitleTextColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaulttitletextcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultListBackColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultlistbackcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultListTextColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultlisttextcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultListActiveColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultlistactivecolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultListActiveTextColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultlistactivetextcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultEditBackColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaulteditbackcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultEditTextColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaultedittextcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultEditSelectionColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaulteditselectioncolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

void MQWidgetBase::GetDefaultEditSelectionTextColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"defaulteditselectiontextcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

MQCanvasColor MQWidgetBase::GetDefaultFrameColor()
{
	MQCanvasColor col;
	GetDefaultFrameColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultBackColor()
{
	MQCanvasColor col;
	GetDefaultBackColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultTextColor()
{
	MQCanvasColor col;
	GetDefaultTextColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultTitleBackColor()
{
	MQCanvasColor col;
	GetDefaultTitleBackColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultTitleTextColor()
{
	MQCanvasColor col;
	GetDefaultTitleTextColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultListBackColor()
{
	MQCanvasColor col;
	GetDefaultListBackColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultListTextColor()
{
	MQCanvasColor col;
	GetDefaultListTextColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultListActiveColor()
{
	MQCanvasColor col;
	GetDefaultListActiveColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultListActiveTextColor()
{
	MQCanvasColor col;
	GetDefaultListActiveTextColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultEditBackColor()
{
	MQCanvasColor col;
	GetDefaultEditBackColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultEditTextColor()
{
	MQCanvasColor col;
	GetDefaultEditTextColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultEditSelectionColor()
{
	MQCanvasColor col;
	GetDefaultEditSelectionColor(col.r, col.g, col.b, col.a);
	return col;
}

MQCanvasColor MQWidgetBase::GetDefaultEditSelectionTextColor()
{
	MQCanvasColor col;
	GetDefaultEditSelectionTextColor(col.r, col.g, col.b, col.a);
	return col;
}


void MQWidgetBase::RegisterSubCommandButton(MQStationPlugin *plugin, MQButton *button, const char *command_str)
{
	MQSendMessageInfo info;
	void *array[5];
	int id = button->GetID();

	array[0] = (void*)"widget";
	array[1] = &id;
	array[2] = (void*)"string";
	array[3] = (void*)command_str;
	array[4] = NULL;

	plugin->GetPlugInID(&info.Product, &info.ID);
	info.option = array;
#if __APPLE__
	info.plugin = plugin;
#endif
	
	MQ_SendMessage(MQMESSAGE_REGISTER_KEYBUTTON, &info);
}

void MQWidgetBase::EnterEventLoop(unsigned int timeout_ms, bool empty_return)
{
	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"entereventloop";
	ptr[2] = (void*)"timeout_ms";
	ptr[3] = &timeout_ms;
	ptr[4] = (void*)"empty_return";
	ptr[5] = &empty_return;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);
}

void MQWidgetBase::ExitEventLoop()
{
	void *ptr[3];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"exiteventloop";
	ptr[2] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);
}

bool MQWidgetBase::CanReceiveTextFromClipboard()
{
	bool result = false;
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"canreceivetextfromclipboard";
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);
	return result;
}

bool MQWidgetBase::GetKeyState(MQKeyCode::KEY_CODE key)
{
	int ikey = (int)key;
	bool result = false;
	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"getkeystate";
	ptr[2] = (void*)"key";
	ptr[3] = &ikey;
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);
	return result;
}

void MQWidgetBase::AddEventCallback(const char *event_type, MQWidgetSharedPtr<MQWidgetEventClosureBase> closure, bool prior)
{
	void *ptr[11];

	ptr[0] = (void*)"type";
	ptr[1] = (void*)event_type;
	ptr[2] = (void*)"proc";
	ptr[3] = (void*)EventCallback;
	ptr[4] = (void*)"pointer";
	ptr[5] = closure.get();
	ptr[6] = (void*)"function";
	ptr[7] = closure.get()->getFunction();
	ptr[8] = (void*)"prior";
	ptr[9] = &prior;
	ptr[10] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_ADD_EVENT, (void*)ptr);

	m_Events.push_back(closure);
}

void MQWidgetBase::RemoveEventCallback(const char *event_type, MQWidgetSharedPtr<MQWidgetEventClosureBase> closure)
{
	std::vector<MQWidgetSharedPtr<MQWidgetEventClosureBase>>::iterator it;
	for(it = m_Events.begin(); it != m_Events.end(); ++it){
		if((*it)->isEqual(closure.get())){
			void *ptr[9];

			ptr[0] = (void*)"type";
			ptr[1] = (void*)event_type;
			ptr[2] = (void*)"proc";
			ptr[3] = (void*)EventCallback;
			ptr[4] = (void*)"pointer";
			ptr[5] = (*it).get();
			ptr[6] = (void*)"function";
			ptr[7] = (*it).get()->getFunction();
			ptr[8] = NULL;
			MQWidget_Value(m_ID, MQWIDGET_REMOVE_EVENT, (void*)ptr);

			m_Events.erase(it);
			break;
		}
	}
}

bool MQWidgetBase::ExistsEventCallback(const char *event_type, MQWidgetSharedPtr<MQWidgetEventClosureBase> closure) const
{
	std::vector<MQWidgetSharedPtr<MQWidgetEventClosureBase>>::const_iterator it;
	for(it = m_Events.begin(); it != m_Events.end(); ++it){
		if((*it)->isEqual(closure.get())){
			return true;
		}
	}
	return false;
}

void MQWidgetBase::AddTimerEventCallback(MQWidgetSharedPtr<MQWidgetEventClosureBase> closure, unsigned int timeout_ms, bool overwrite)
{
	void *ptr[13];

	ptr[0] = (void*)"type";
	ptr[1] = (void*)"timer";
	ptr[2] = (void*)"proc";
	ptr[3] = (void*)EventCallback;
	ptr[4] = (void*)"pointer";
	ptr[5] = closure.get();
	ptr[6] = (void*)"function";
	ptr[7] = closure.get()->getFunction();
	ptr[8] = (void*)"timeout_ms";
	ptr[9] = &timeout_ms;
	ptr[10] = (void*)"overwrite";
	ptr[11] = &overwrite;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_ADD_EVENT, (void*)ptr);

	if(overwrite){
		std::vector<MQWidgetSharedPtr<MQWidgetEventClosureBase>>::iterator it;
		for(it = m_Events.begin(); it != m_Events.end(); ++it){
			if((*it)->isEqual(closure.get())){
				return;
			}
		}
	}
	m_Events.push_back(closure);
}

BOOL MQAPICALL MQWidgetBase::EventCallback(MQDocument doc, void **params, void *option)
{
	int target_id = ExtractEventOptionInt(params, "target_id", NullID);
	int sender_id = ExtractEventOptionInt(params, "sender_id", NullID);
	bool *finished = (bool*)ExtractEventOption(params, "finished");
	const char *type = (const char *)ExtractEventOption(params, "type");
	if(type == NULL) return FALSE;

	MQWidgetBase *target = FindWidgetByID(target_id);
	if(target != NULL){
		for(size_t i=0; i<target->m_Events.size(); i++){
			if(target->m_Events[i].get() == option){
				MQWidgetBase *sender = FindWidgetByID(sender_id);
				if( strcmp(type, "leftdown") == 0 || 
					strcmp(type, "leftup") == 0 || 
					strcmp(type, "leftdoubleclick") == 0 || 
					strcmp(type, "middledown") == 0 || 
					strcmp(type, "middleup") == 0 || 
					strcmp(type, "middledoubleclick") == 0 || 
					strcmp(type, "rightdown") == 0 || 
					strcmp(type, "rightup") == 0 || 
					strcmp(type, "rightdoubleclick") == 0 || 
					strcmp(type, "mousemove") == 0 || 
					strcmp(type, "mousewheel") == 0 )
				{
					MQWidgetMouseParam param;
					param.ClientPos.x = ExtractEventOptionInt(params, "client_x", 0);
					param.ClientPos.y = ExtractEventOptionInt(params, "client_y", 0);
					param.ScreenPos.x = ExtractEventOptionInt(params, "screen_x", 0);
					param.ScreenPos.y = ExtractEventOptionInt(params, "screen_y", 0);
					param.DownPos.x = ExtractEventOptionInt(params, "down_x", 0);
					param.DownPos.y = ExtractEventOptionInt(params, "down_y", 0);
					param.LastPos.x = ExtractEventOptionInt(params, "last_x", 0);
					param.LastPos.y = ExtractEventOptionInt(params, "last_y", 0);
					param.Wheel = ExtractEventOptionInt(params, "wheel_delta", 0);
					param.Pressure = ExtractEventOptionFloat(params, "pressure", 0.0f);
					param.Finished = false;

					DWORD button_state = (DWORD)ExtractEventOptionInt(params, "button_state", 0);
					param.LButton = (button_state & MK_LBUTTON) ? TRUE : FALSE;
					param.MButton = (button_state & MK_MBUTTON) ? TRUE : FALSE;
					param.RButton = (button_state & MK_RBUTTON) ? TRUE : FALSE;
					param.Shift = (button_state & MK_SHIFT) ? TRUE : FALSE;
					param.Ctrl = (button_state & MK_CONTROL) ? TRUE : FALSE;
					param.Alt = (button_state & MK_ALT) ? TRUE : FALSE;

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					if(param.Finished && finished != NULL){
						*finished = true;
					}
					return result;
				}
				else if(
					strcmp(type, "keydown") == 0 || 
					strcmp(type, "keyup") == 0 )
				{
					MQWidgetKeyParam param;
					param.Key = (MQKeyCode::KEY_CODE)ExtractEventOptionInt(params, "key", MQKeyCode::KEY_NONE);
					param.AutoRepeat = ExtractEventOptionInt(params, "auto_repeat", 0) != 0;

					DWORD button_state = (DWORD)ExtractEventOptionInt(params, "button_state", 0);
					param.LButton = (button_state & MK_LBUTTON) ? TRUE : FALSE;
					param.MButton = (button_state & MK_MBUTTON) ? TRUE : FALSE;
					param.RButton = (button_state & MK_RBUTTON) ? TRUE : FALSE;
					param.Shift = (button_state & MK_SHIFT) ? TRUE : FALSE;
					param.Ctrl = (button_state & MK_CONTROL) ? TRUE : FALSE;
					param.Alt = (button_state & MK_ALT) ? TRUE : FALSE;
					param.Finished = false;

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					if(param.Finished && finished != NULL){
						*finished = true;
					}
					return result;
				}
				else if(strcmp(type, "paint") == 0)
				{
					MQWidgetPaintParam param;
					param.Canvas = new MQCanvas(ExtractEventOption(params, "canvas"));
					param.Interrupted = (bool*)ExtractEventOption(params, "interrupted");

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					delete param.Canvas;
					return result;
				}
				else if(strcmp(type, "listdrawitem") == 0)
				{
					int *px = (int*)ExtractEventOption(params, "x");
					int *py = (int*)ExtractEventOption(params, "y");
					int *pw = (int*)ExtractEventOption(params, "width");
					int *ph = (int*)ExtractEventOption(params, "height");

					MQListBoxDrawItemParam param;
					param.Canvas = new MQCanvas(ExtractEventOption(params, "canvas"));
					param.ItemIndex = ExtractEventOptionInt(params, "index", -1);
					param.X = *px;
					param.Y = *py;
					param.Width = *pw;
					param.Height = *ph;

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					delete param.Canvas;
					*px = param.X;
					*py = param.Y;
					*pw = param.Width;
					*ph = param.Height;
					return result;
				}
				else if(strcmp(type, "treelistdrawitem") == 0)
				{
					int *px = (int*)ExtractEventOption(params, "x");
					int *py = (int*)ExtractEventOption(params, "y");
					int *pw = (int*)ExtractEventOption(params, "width");
					int *ph = (int*)ExtractEventOption(params, "height");

					MQTreeListBoxDrawItemParam param;
					param.Canvas = new MQCanvas(ExtractEventOption(params, "canvas"));
					param.ItemIndex = ExtractEventOptionInt(params, "index", -1);
					param.ItemID = ExtractEventOptionInt(params, "id", -1);
					param.X = *px;
					param.Y = *py;
					param.Width = *pw;
					param.Height = *ph;

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					delete param.Canvas;
					*px = param.X;
					*py = param.Y;
					*pw = param.Width;
					*ph = param.Height;
					return result;
				}
				else if(strcmp(type, "memodrawitem") == 0)
				{
					int *px = (int*)ExtractEventOption(params, "x");
					int *py = (int*)ExtractEventOption(params, "y");
					int *pw = (int*)ExtractEventOption(params, "width");
					int *ph = (int*)ExtractEventOption(params, "height");

					MQMemoDrawItemParam param;
					param.Canvas = new MQCanvas(ExtractEventOption(params, "canvas"));
					param.Line = ExtractEventOptionInt(params, "line", -1);
					param.StartPos = *(size_t*)ExtractEventOption(params, "start");
					param.EndPos = *(size_t*)ExtractEventOption(params, "end");
					param.X = *px;
					param.Y = *py;
					param.Width = *pw;
					param.Height = *ph;

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					delete param.Canvas;
					*px = param.X;
					*py = param.Y;
					*pw = param.Width;
					*ph = param.Height;
					return result;
				}
				else if(strcmp(type, "timer") == 0)
				{
					MQWidgetSharedPtr<MQWidgetEventClosureBase> ev = target->m_Events[i];
					target->m_Events.erase(target->m_Events.begin() + i);
					return ev->invoke(sender, doc, NULL);
				}
				else if(strcmp(type, "closequery") == 0)
				{
					MQWidgetCloseQueryParam param;
					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);

					if(finished != nullptr && param.Canceled)
						*finished = param.Canceled;
					return result;
				}
				else if(strcmp(type, "dragover") == 0)
				{
					MQWidgetDragOverParam param;
					param.ClientPos.x = ExtractEventOptionInt(params, "client_x", 0);
					param.ClientPos.y = ExtractEventOptionInt(params, "client_y", 0);
					param.ScreenPos.x = ExtractEventOptionInt(params, "screen_x", 0);
					param.ScreenPos.y = ExtractEventOptionInt(params, "screen_y", 0);
					bool *result_ptr = (bool*)ExtractEventOption(params, "result");
					param.Result = *result_ptr;

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					*result_ptr = param.Result;
					return result;
				}
				else if(strcmp(type, "dropfiles") == 0)
				{
					MQWidgetDropFilesParam param;
					param.ClientPos.x = ExtractEventOptionInt(params, "client_x", 0);
					param.ClientPos.y = ExtractEventOptionInt(params, "client_y", 0);
					param.ScreenPos.x = ExtractEventOptionInt(params, "screen_x", 0);
					param.ScreenPos.y = ExtractEventOptionInt(params, "screen_y", 0);
					const wchar_t **files = (const wchar_t **)ExtractEventOption(params, "files");
					for(; *files != nullptr; files++){
						param.Files.push_back(*files);
					}

					BOOL result = target->m_Events[i]->invoke(sender, doc, &param);
					return result;
				}
				else
				{
					return target->m_Events[i]->invoke(sender, doc, NULL);
				}
			}
		}
	}

	return FALSE;
}

//---------------------------------------------------------------------------
//  class MQFrameBase
//---------------------------------------------------------------------------
MQFrameBase::MQFrameBase() : MQWidgetBase()
{
}

MQFrameBase::MQFrameBase(int id) : MQWidgetBase(id)
{
}

MQFrameBase::~MQFrameBase()
{
}

MQFrameBase::MQFrameAlignment MQFrameBase::GetAlignment()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "horz") == 0) return ALIGN_HORIZONTAL;
	if(strcmp(align_str, "vert") == 0) return ALIGN_VERTICAL;
	return ALIGN_NONE;
}

void MQFrameBase::SetAlignment(MQFrameAlignment align)
{
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	switch(align){
	case ALIGN_HORIZONTAL: ptr[1] = (void*)"horz"; break;
	case ALIGN_VERTICAL:   ptr[1] = (void*)"vert"; break;
	default: ptr[1] = (void*)"none"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQFrameBase::GetMultiColumn()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"multicolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFrameBase::SetMultiColumn(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"multicolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQFrameBase::GetMatrixColumn()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"matrixcolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFrameBase::SetMatrixColumn(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"matrixcolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQFrameBase::GetUniformSize()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"uniformsize";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFrameBase::SetUniformSize(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"uniformsize";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQFrameBase::GetSplit()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"split";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFrameBase::SetSplit(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"split";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQFrame
//---------------------------------------------------------------------------
MQFrame::MQFrame() : MQFrameBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"frame";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQFrame::MQFrame(int id) : MQFrameBase(id)
{
}

MQFrame::~MQFrame()
{
}

void MQFrame::GetBackColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"backcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

MQCanvasColor MQFrame::GetBackColor()
{
	MQCanvasColor col;
	GetBackColor(col.r, col.g, col.b, col.a);
	return col;
}

void MQFrame::SetBackColor(int r, int g, int b, int a)
{
	int array[4] = {r,g,b,a};
	void *ptr[9];
	ptr[0] = (void*)"backcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQFrame::SetBackColor(MQCanvasColor col)
{
	SetBackColor(col.r, col.g, col.b, col.a);
}

//---------------------------------------------------------------------------
//  class MQDockFrame
//---------------------------------------------------------------------------
MQDockFrame::MQDockFrame() : MQFrameBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"dockframe";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQDockFrame::MQDockFrame(int id) : MQFrameBase(id)
{
}

MQDockFrame::~MQDockFrame()
{
}

void MQDockFrame::RegisterDockableWindow(MQDockWindow *dock_window)
{
	if(dock_window == NULL) return;
	int windowID = dock_window->GetID();
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"registerdockablewindow";
	ptr[2] = (void*)"window";
	ptr[3] = &windowID;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);

	m_DockWindows.push_back(std::make_pair(windowID, dock_window));
}

void MQDockFrame::GetDockedWindowStatus(std::map<MQDockWindow*, MQDockWindow::MQDockStatus>& status)
{
	std::vector<MQDockWindow*> windows;
	std::vector<int> windowIDs;
	for(auto it = m_DockWindows.begin(); it != m_DockWindows.end(); ){
		if(s_WidgetIDMap.end() == s_WidgetIDMap.find((*it).first)){
			it = m_DockWindows.erase(it);
		}else{
			windows.push_back((*it).second);
			windowIDs.push_back((*it).first);
			++it;
		}
	}
	int length = (int)windows.size();
	std::vector<int> orders(windows.size(), -1);
	std::vector<int> parentIDs(windows.size(), NullID);
	std::vector<int> directions(windows.size(), 0);
	std::vector<double> sizerates(windows.size(), 0.0);

	void *ptr[15];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"dockedwindowstatus";
	ptr[2] = (void*)"length";
	ptr[3] = &length;
	ptr[4] = (void*)"window";
	ptr[5] = windowIDs.data();
	ptr[6] = (void*)"order";
	ptr[7] = orders.data();
	ptr[8] = (void*)"parent";
	ptr[9] = parentIDs.data();
	ptr[10] = (void*)"direction";
	ptr[11] = directions.data();
	ptr[12] = (void*)"sizerate";
	ptr[13] = sizerates.data();
	ptr[14] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);

	status.clear();
	for(size_t i=0; i<windows.size(); i++){
		if(orders[i] >= 0){
			MQDockWindow::MQDockStatus s;
			s.Order = orders[i];
			s.Parent = nullptr;
			if(parentIDs[i] != NullID){
				for(size_t j=0; j<windowIDs.size(); j++){
					if(parentIDs[i] == windowIDs[j]){
						s.Parent = windows[j];
						break;
					}
				}
			}
			s.Direction = (MQDockWindow::MQDockDirection)directions[i];
			s.SizeRate = sizerates[i];
			status.insert(std::make_pair(windows[i], s));
		}
	}
}

void MQDockFrame::GetBackColor(int& r, int& g, int& b, int& a)
{
	int array[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"backcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
	a = array[3];
}

MQCanvasColor MQDockFrame::GetBackColor()
{
	MQCanvasColor col;
	GetBackColor(col.r, col.g, col.b, col.a);
	return col;
}

void MQDockFrame::SetBackColor(int r, int g, int b, int a)
{
	int array[4] = {r,g,b,a};
	void *ptr[9];
	ptr[0] = (void*)"backcolor.rgba";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQDockFrame::SetBackColor(MQCanvasColor col)
{
	SetBackColor(col.r, col.g, col.b, col.a);
}

//---------------------------------------------------------------------------
//  class MQGroupBox
//---------------------------------------------------------------------------
MQGroupBox::MQGroupBox() : MQFrameBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"groupbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQGroupBox::MQGroupBox(int id) : MQFrameBase(id)
{
}

MQGroupBox::~MQGroupBox()
{
}

std::wstring MQGroupBox::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQGroupBox::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQGroupBox::GetCanMinimize()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"canminimize";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQGroupBox::SetCanMinimize(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"canminimize";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQGroupBox::GetMinimized()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"minimized";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQGroupBox::SetMinimized(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"minimized";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQGroupBox::GetShowTitle()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"showtitle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQGroupBox::SetShowTitle(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"showtitle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQScrollBox
//---------------------------------------------------------------------------
MQScrollBox::MQScrollBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"scrollbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQScrollBox::MQScrollBox(int id) : MQWidgetBase(id)
{
}

MQScrollBox::~MQScrollBox()
{
}

MQScrollBox::MQScrollBoxBarStatus MQScrollBox::GetHorzBarStatus()
{
	char *status_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"horzbarstatus";
	ptr[1] = &status_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(status_str, "auto") == 0) return SCROLLBAR_AUTO;
	if(strcmp(status_str, "on") == 0) return SCROLLBAR_ON;
	if(strcmp(status_str, "off") == 0) return SCROLLBAR_OFF;
	return SCROLLBAR_AUTO;
}

void MQScrollBox::SetHorzBarStatus(MQScrollBoxBarStatus value)
{
	void *ptr[3];
	ptr[0] = (void*)"horzbarstatus";
	switch(value){
	default:
	case SCROLLBAR_AUTO: ptr[1] = (void*)"auto"; break;
	case SCROLLBAR_OFF:  ptr[1] = (void*)"off"; break;
	case SCROLLBAR_ON:   ptr[1] = (void*)"on"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQScrollBox::MQScrollBoxBarStatus MQScrollBox::GetVertBarStatus()
{
	char *status_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"vertbarstatus";
	ptr[1] = &status_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(status_str, "auto") == 0) return SCROLLBAR_AUTO;
	if(strcmp(status_str, "on") == 0) return SCROLLBAR_ON;
	if(strcmp(status_str, "off") == 0) return SCROLLBAR_OFF;
	return SCROLLBAR_AUTO;
}

void MQScrollBox::SetVertBarStatus(MQScrollBoxBarStatus value)
{
	void *ptr[3];
	ptr[0] = (void*)"vertbarstatus";
	switch(value){
	default:
	case SCROLLBAR_AUTO: ptr[1] = (void*)"auto"; break;
	case SCROLLBAR_OFF:  ptr[1] = (void*)"off"; break;
	case SCROLLBAR_ON:   ptr[1] = (void*)"on"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQScrollBox::GetAutoWidgetScroll()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"autowidgetscroll";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQScrollBox::SetAutoWidgetScroll(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"autowidgetscroll";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}



//---------------------------------------------------------------------------
//  class MQTab
//---------------------------------------------------------------------------
MQTab::MQTab() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"tab";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQTab::MQTab(int id) : MQWidgetBase(id)
{
}

MQTab::~MQTab()
{
}

std::wstring MQTab::GetTabTitle(int index)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"title.text.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"title.text";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQTab::SetTabTitle(int index, const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"title.text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQTab::GetCurrentPage()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"currentpage";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTab::SetCurrentPage(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"currentpage";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTab::GetShowTab()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"showtab";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTab::SetShowTab(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"showtab";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTab::GetExclusive()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"exclusive";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTab::SetExclusive(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"exclusive";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQButton
//---------------------------------------------------------------------------
MQButton::MQButton() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"button";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQButton::MQButton(int id) : MQWidgetBase(id)
{
}

MQButton::~MQButton()
{
}

std::wstring MQButton::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQButton::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQButton::GetFontName()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"fontname.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"fontname";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQButton::SetFontName(const std::wstring& value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontname";
	ptr[1] = (void*)value.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQButton::GetFontBold()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetFontBold(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::GetFontColor(int& r, int& g, int& b, int& a)
{
	int value[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = value[0];
	g = value[1];
	b = value[2];
	a = value[3];
}

void MQButton::SetFontColor(int r, int g, int b, int a)
{
	int value[4] = {r,g,b,a};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQCanvasColor MQButton::GetFontColor()
{
	MQCanvasColor c;
	GetFontColor(c.r, c.g, c.b, c.a);
	return c;
}

void MQButton::SetFontColor(const MQCanvasColor& color)
{
	SetFontColor(color.r, color.g, color.b, color.a);
}

double MQButton::GetFontScale()
{
	double value = 0.0;
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetFontScale(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQButton::MQButtonTextAlignment MQButton::GetAlignment()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "left") == 0) return ALIGN_LEFT;
	if(strcmp(align_str, "center") == 0) return ALIGN_CENTER;
	if(strcmp(align_str, "right") == 0) return ALIGN_RIGHT;
	if(strcmp(align_str, "center_except_image") == 0) return ALIGN_CENTER_EXCEPT_IMAGE;
	return ALIGN_LEFT;
}

void MQButton::SetAlignment(MQButtonTextAlignment value)
{
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	switch(value){
	default:
	case ALIGN_LEFT:   ptr[1] = (void*)"left"; break;
	case ALIGN_CENTER: ptr[1] = (void*)"center"; break;
	case ALIGN_RIGHT:  ptr[1] = (void*)"right"; break;
	case ALIGN_CENTER_EXCEPT_IMAGE: ptr[1] = (void*)"center_except_image"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQButton::GetToggle()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"toggle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetToggle(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"toggle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQButton::GetDown()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"down";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetDown(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"down";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQButton::GetRepeat()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"repeat";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetRepeat(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"repeat";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQButton::GetChain()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"chain";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetChain(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"chain";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQButton::GetFlat()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"flat";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetFlat(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"flat";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQButton::GetPaddingX()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"paddingx";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetPaddingX(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"paddingx";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQButton::GetPaddingY()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"paddingy";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQButton::SetPaddingY(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"paddingy";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::SetDefault(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"default";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::SetCancel(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"cancel";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::SetModalResult(MQDialog::DIALOG_RESULT value)
{
	void *ptr[3];
	ptr[0] = (void*)"modalresult";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::SetSystemSVGFile(const wchar_t *filename)
{
	void *ptr[3];
	ptr[0] = (void*)"systemsvgfile";
	ptr[1] = (void*)filename;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::SetImageScale(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"imagescale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQButton::GetImageScale()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"imagescale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

MQButton::MQButtonImagePosition MQButton::GetImagePosition()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"imagepos";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "left") == 0) return IMAGE_LEFT;
	if(strcmp(align_str, "right") == 0) return IMAGE_RIGHT;
	if(strcmp(align_str, "top") == 0) return IMAGE_TOP;
	if(strcmp(align_str, "bottom") == 0) return IMAGE_BOTTOM;
	return IMAGE_LEFT;
}

void MQButton::SetImagePosition(MQButtonImagePosition value)
{
	void *ptr[3];
	ptr[0] = (void*)"imagepos";
	switch(value){
	default:
	case IMAGE_LEFT:   ptr[1] = (void*)"left"; break;
	case IMAGE_RIGHT:  ptr[1] = (void*)"right"; break;
	case IMAGE_TOP:    ptr[1] = (void*)"top"; break;
	case IMAGE_BOTTOM: ptr[1] = (void*)"bottom"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQButton::ReorderOKButton(MQWidgetBase *parent, MQButton *btn1, MQButton *btn2)
{
#if __APPLE__
	if(parent == nullptr || btn1 == nullptr || btn2 == nullptr)
		return;

	int index1 = parent->GetIndexOfChild(btn1);
	int index2 = parent->GetIndexOfChild(btn2);
	if(index1 < 0 || index2 < 0)
		return;

	parent->RemoveChild(btn1);
	parent->RemoveChild(btn2);
	
	if(index1 < index2){
		parent->InsertChild(btn2, index1);
		parent->InsertChild(btn1, index2);
	}else{
		parent->InsertChild(btn1, index2);
		parent->InsertChild(btn2, index1);
	}
	
	double d1, d2;
	d1 = btn1->GetFillBeforeRate();
	d2 = btn2->GetFillBeforeRate();
	btn1->SetFillBeforeRate(d2);
	btn2->SetFillBeforeRate(d1);
	d1 = btn1->GetFillAfterRate();
	d2 = btn2->GetFillAfterRate();
	btn1->SetFillAfterRate(d2);
	btn2->SetFillAfterRate(d1);
#endif
}

//---------------------------------------------------------------------------
//  class MQCheckBox
//---------------------------------------------------------------------------
MQCheckBox::MQCheckBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"checkbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQCheckBox::MQCheckBox(int id) : MQWidgetBase(id)
{
}

MQCheckBox::~MQCheckBox()
{
}

bool MQCheckBox::GetChecked()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"checked";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckBox::SetChecked(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"checked";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQCheckBox::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQCheckBox::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQCheckBox::GetFontColor(int& r, int& g, int& b, int& a)
{
	int value[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = value[0];
	g = value[1];
	b = value[2];
	a = value[3];
}

void MQCheckBox::SetFontColor(int r, int g, int b, int a)
{
	int value[4] = {r,g,b,a};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQCanvasColor MQCheckBox::GetFontColor()
{
	MQCanvasColor c;
	GetFontColor(c.r, c.g, c.b, c.a);
	return c;
}

void MQCheckBox::SetFontColor(const MQCanvasColor& color)
{
	SetFontColor(color.r, color.g, color.b, color.a);
}

bool MQCheckBox::GetShadowText()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"shadowtext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckBox::SetShadowText(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"shadowtext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQRadioButton
//---------------------------------------------------------------------------
MQRadioButton::MQRadioButton() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"radiobutton";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQRadioButton::MQRadioButton(int id) : MQWidgetBase(id)
{
}

MQRadioButton::~MQRadioButton()
{
}

bool MQRadioButton::GetChecked()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"checked";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQRadioButton::SetChecked(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"checked";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQRadioButton::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQRadioButton::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQRadioButton::GetFontColor(int& r, int& g, int& b, int& a)
{
	int value[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = value[0];
	g = value[1];
	b = value[2];
	a = value[3];
}

void MQRadioButton::SetFontColor(int r, int g, int b, int a)
{
	int value[4] = {r,g,b,a};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQCanvasColor MQRadioButton::GetFontColor()
{
	MQCanvasColor c;
	GetFontColor(c.r, c.g, c.b, c.a);
	return c;
}

void MQRadioButton::SetFontColor(const MQCanvasColor& color)
{
	SetFontColor(color.r, color.g, color.b, color.a);
}

bool MQRadioButton::GetShadowText()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"shadowtext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQRadioButton::SetShadowText(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"shadowtext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQComboBox
//---------------------------------------------------------------------------
MQComboBox::MQComboBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"combobox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQComboBox::MQComboBox(int id) : MQWidgetBase(id)
{
}

MQComboBox::~MQComboBox()
{
}

int MQComboBox::GetCurrentIndex()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"currentindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQComboBox::SetCurrentIndex(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"currentindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQComboBox::AddItem(const std::wstring& text)
{
	int result = -1;
	void *ptr[7];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQComboBox::AddItem(const std::wstring& text, __int64 tag)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = (void*)"tag";
	ptr[7] = &tag;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQComboBox::DeleteItem(int index)
{
	void *ptr[5];
	ptr[0] = (void*)"deleteitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQComboBox::ClearItems()
{
	void *ptr[3];
	ptr[0] = (void*)"clearitems";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQComboBox::GetItemCount()
{
	int value = 0;
	void *ptr[3];

	ptr[0] = (void*)"item.count";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

std::wstring MQComboBox::GetItem(int index)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.text.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.text";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQComboBox::SetItem(int index, const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

__int64 MQComboBox::GetItemTag(int index)
{
	__int64 value = 0;
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQComboBox::SetItemTag(int index, __int64 tag)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &tag;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQComboBox::GetNumVisible()
{
	int  value = 0;
	void *ptr[3];
	ptr[0] = (void*)"numvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQComboBox::SetNumVisible(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"numvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQListBox
//---------------------------------------------------------------------------
MQListBox::MQListBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"listbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQListBox::MQListBox(int id) : MQWidgetBase(id)
{
}

MQListBox::~MQListBox()
{
}

int MQListBox::GetCurrentIndex()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"currentindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetCurrentIndex(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"currentindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQListBox::BeginUpdate()
{
	void *ptr[3];
	ptr[0] = (void*)"beginupdate";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQListBox::EndUpdate()
{
	void *ptr[3];
	ptr[0] = (void*)"endupdate";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQListBox::AddItem(const std::wstring& text)
{
	int result = -1;
	void *ptr[7];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQListBox::AddItem(const std::wstring& text, __int64 tag)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = (void*)"tag";
	ptr[7] = &tag;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQListBox::DeleteItem(int index)
{
	void *ptr[5];
	ptr[0] = (void*)"deleteitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQListBox::ClearItems()
{
	void *ptr[3];
	ptr[0] = (void*)"clearitems";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQListBox::GetItemCount()
{
	int value = 0;
	void *ptr[3];

	ptr[0] = (void*)"item.count";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

std::wstring MQListBox::GetItem(int index)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.text.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.text";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQListBox::SetItem(int index, const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

__int64 MQListBox::GetItemTag(int index)
{
	__int64 value = 0;
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetItemTag(int index, __int64 tag)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &tag;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQListBox::GetItemSelected(int index)
{
	bool value = false;
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.selected";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetItemSelected(int index, bool selected)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.selected";
	ptr[3] = &selected;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQListBox::GetItemHint(int index)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.hint.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.hint";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQListBox::SetItemHint(int index, const std::wstring& hint)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.hint";
	ptr[3] = (void*)hint.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQListBox::SetItemDIB(int index, void *header, void *buffer)
{
	void *ptr[7];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.dib.header";
	ptr[3] = header;
	ptr[4] = (void*)"item.dib.buffer";
	ptr[5] = buffer;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQListBox::GetVisibleRow()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"visiblerow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetVisibleRow(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"visiblerow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQListBox::GetLineHeightRate()
{
	double value = 1.0;
	void *ptr[3];
	ptr[0] = (void*)"lineheightrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetLineHeightRate(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"lineheightrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQListBox::GetVertScrollVisible()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"vertscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetVertScrollVisible(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"vertscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQListBox::GetMultiSelect()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetMultiSelect(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQListBox::MQListBoxStyle MQListBox::GetListStyle()
{
	char *style_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"liststyle";
	ptr[1] = &style_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(style_str, "normal") == 0) return STYLE_NORMAL;
	if(strcmp(style_str, "icon") == 0) return STYLE_ICON;
	if(strcmp(style_str, "icononly") == 0) return STYLE_ICON_ONLY;
	return STYLE_NORMAL;
}

void MQListBox::SetListStyle(MQListBoxStyle style)
{
	void *ptr[3];
	ptr[0] = (void*)"liststyle";
	switch(style){
	default:
	case STYLE_NORMAL: ptr[1] = (void*)"normal"; break;
	case STYLE_ICON: ptr[1] = (void*)"icon"; break;
	case STYLE_ICON_ONLY:  ptr[1] = (void*)"icononly"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQListBox::GetIconSizeRate()
{
	double value = 1.0;
	void *ptr[3];
	ptr[0] = (void*)"iconsizerate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQListBox::SetIconSizeRate(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"iconsizerate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQListBox::ClearSelection()
{
	void *ptr[3];
	ptr[0] = (void*)"clearselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQListBox::MakeItemVisible(int index)
{
	void *ptr[5];
	ptr[0] = (void*)"makeitemvisible";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQListBox::HitTestItem(int x, int y)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"hittestitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"x";
	ptr[3] = &x;
	ptr[4] = (void*)"y";
	ptr[5] = &y;
	ptr[6] = (void*)"result";
	ptr[7] = &result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQListBox::GetItemRect(int index, int& x, int& y, int& w, int& h)
{
	void *ptr[13];
	ptr[0] = (void*)"getitemrect";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = (void*)"x";
	ptr[5] = &x;
	ptr[6] = (void*)"y";
	ptr[7] = &y;
	ptr[8] = (void*)"w";
	ptr[9] = &w;
	ptr[10] = (void*)"h";
	ptr[11] = &h;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQCheckListBox
//---------------------------------------------------------------------------
MQCheckListBox::MQCheckListBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"checklistbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQCheckListBox::MQCheckListBox(int id) : MQWidgetBase(id)
{
}

MQCheckListBox::~MQCheckListBox()
{
}

int MQCheckListBox::GetCurrentIndex()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"currentindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetCurrentIndex(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"currentindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQCheckListBox::BeginUpdate()
{
	void *ptr[3];
	ptr[0] = (void*)"beginupdate";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQCheckListBox::EndUpdate()
{
	void *ptr[3];
	ptr[0] = (void*)"endupdate";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQCheckListBox::AddItem(const std::wstring& text)
{
	int result = -1;
	void *ptr[7];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQCheckListBox::AddItem(const std::wstring& text, __int64 tag)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = (void*)"tag";
	ptr[7] = &tag;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQCheckListBox::DeleteItem(int index)
{
	void *ptr[5];
	ptr[0] = (void*)"deleteitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQCheckListBox::ClearItems()
{
	void *ptr[3];
	ptr[0] = (void*)"clearitems";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQCheckListBox::GetItemCount()
{
	int value = 0;
	void *ptr[3];

	ptr[0] = (void*)"item.count";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

std::wstring MQCheckListBox::GetItem(int index)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.text.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.text";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQCheckListBox::SetItem(int index, const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

__int64 MQCheckListBox::GetItemTag(int index)
{
	__int64 value = 0;
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetItemTag(int index, __int64 tag)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &tag;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQCheckListBox::GetItemSelected(int index)
{
	bool value = false;
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.selected";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetItemSelected(int index, bool selected)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.selected";
	ptr[3] = &selected;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQCheckListBox::GetItemChecked(int index)
{
	bool value = false;
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.checked";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetItemChecked(int index, bool checked)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.checked";
	ptr[3] = &checked;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQCheckListBox::GetItemHint(int index)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.hint.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.hint";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQCheckListBox::SetItemHint(int index, const std::wstring& hint)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"item.hint";
	ptr[3] = (void*)hint.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQCheckListBox::GetVisibleRow()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"visiblerow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetVisibleRow(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"visiblerow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQCheckListBox::GetLineHeightRate()
{
	double value = 1.0;
	void *ptr[3];
	ptr[0] = (void*)"lineheightrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetLineHeightRate(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"lineheightrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQCheckListBox::GetVertScrollVisible()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"vertscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetVertScrollVisible(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"vertscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQCheckListBox::GetMultiSelect()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQCheckListBox::SetMultiSelect(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQCheckListBox::ClearSelection()
{
	void *ptr[3];
	ptr[0] = (void*)"clearselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQCheckListBox::MakeItemVisible(int index)
{
	void *ptr[5];
	ptr[0] = (void*)"makeitemvisible";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQCheckListBox::HitTestItem(int x, int y)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"hittestitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"x";
	ptr[3] = &x;
	ptr[4] = (void*)"y";
	ptr[5] = &y;
	ptr[6] = (void*)"result";
	ptr[7] = &result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQCheckListBox::GetItemRect(int index, int& x, int& y, int& w, int& h)
{
	void *ptr[13];
	ptr[0] = (void*)"getitemrect";
	ptr[1] = NULL;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = (void*)"x";
	ptr[5] = &x;
	ptr[6] = (void*)"y";
	ptr[7] = &y;
	ptr[8] = (void*)"w";
	ptr[9] = &w;
	ptr[10] = (void*)"h";
	ptr[11] = &h;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQTreeListBox
//---------------------------------------------------------------------------
MQTreeListBox::MQTreeListBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"treelistbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQTreeListBox::MQTreeListBox(int id) : MQWidgetBase(id)
{
}

MQTreeListBox::~MQTreeListBox()
{
}

int MQTreeListBox::GetCurrentID()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"currentid";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetCurrentID(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"currentid";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQTreeListBox::BeginUpdate()
{
	void *ptr[3];
	ptr[0] = (void*)"beginupdate";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQTreeListBox::EndUpdate()
{
	void *ptr[3];
	ptr[0] = (void*)"endupdate";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQTreeListBox::AddItem(const std::wstring& text)
{
	int result = -1;
	void *ptr[7];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQTreeListBox::AddItem(const std::wstring& text, __int64 tag)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = (void*)"tag";
	ptr[7] = &tag;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQTreeListBox::AddItem(int parent_id, const std::wstring& text)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"parent";
	ptr[3] = &parent_id;
	ptr[4] = (void*)"text";
	ptr[5] = (void*)text.c_str();
	ptr[6] = (void*)"result";
	ptr[7] = &result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQTreeListBox::AddItem(int parent_id, const std::wstring& text, __int64 tag)
{
	int result = -1;
	void *ptr[11];
	ptr[0] = (void*)"additem";
	ptr[1] = NULL;
	ptr[2] = (void*)"parent";
	ptr[3] = &parent_id;
	ptr[4] = (void*)"text";
	ptr[5] = (void*)text.c_str();
	ptr[6] = (void*)"result";
	ptr[7] = &result;
	ptr[8] = (void*)"tag";
	ptr[9] = &tag;
	ptr[10] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQTreeListBox::DeleteItem(int id)
{
	void *ptr[5];
	ptr[0] = (void*)"deleteitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"id";
	ptr[3] = &id;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQTreeListBox::ClearItems()
{
	void *ptr[3];
	ptr[0] = (void*)"clearitems";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQTreeListBox::ReparentItem(int id, int new_parent_id)
{
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"parent";
	ptr[3] = &new_parent_id;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQTreeListBox::GetItemCount()
{
	int value = 0;
	void *ptr[3];

	ptr[0] = (void*)"item.count";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

int MQTreeListBox::GetItemIDByIndex(int index)
{
	int id = -1;
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"index";
	ptr[3] = &index;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return id;
}

int MQTreeListBox::GetItemParent(int id)
{
	int value = -1;
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"parent";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

std::vector<int> MQTreeListBox::GetItemChildren(int id)
{
	int num = 0;
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"child.num";
	ptr[3] = &num;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	if(num == 0) return std::vector<int>();

	std::vector<int> children(num);
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"children";
	ptr[3] = &(*children.begin());
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return children;
}

std::wstring MQTreeListBox::GetItem(int id)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.text.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.text";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQTreeListBox::SetItem(int id, const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

__int64 MQTreeListBox::GetItemTag(int id)
{
	__int64 value = 0;
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetItemTag(int id, __int64 tag)
{
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.tag";
	ptr[3] = &tag;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTreeListBox::GetItemSelected(int id)
{
	bool value = false;
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.selected";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetItemSelected(int id, bool selected)
{
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.selected";
	ptr[3] = &selected;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQTreeListBox::GetItemHint(int id)
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.hint.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"item.hint";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQTreeListBox::SetItemHint(int id, const std::wstring& hint)
{
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.hint";
	ptr[3] = (void*)hint.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTreeListBox::GetItemCollapsed(int id)
{
	bool value = false;
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.collapsed";
	ptr[3] = &value;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetItemCollapsed(int id, bool collapsed)
{
	void *ptr[5];
	ptr[0] = (void*)"id";
	ptr[1] = &id;
	ptr[2] = (void*)"item.collapsed";
	ptr[3] = &collapsed;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQTreeListBox::GetVisibleRow()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"visiblerow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetVisibleRow(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"visiblerow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQTreeListBox::GetLineHeightRate()
{
	double value = 1.0;
	void *ptr[3];
	ptr[0] = (void*)"lineheightrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetLineHeightRate(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"lineheightrate";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTreeListBox::GetHorzScrollVisible()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"horzscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetHorzScrollVisible(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"horzscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTreeListBox::GetVertScrollVisible()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"vertscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetVertScrollVisible(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"vertscrollvisible";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQTreeListBox::GetMultiSelect()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQTreeListBox::SetMultiSelect(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQTreeListBox::ClearSelection()
{
	void *ptr[3];
	ptr[0] = (void*)"clearselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQTreeListBox::MakeItemVisible(int id)
{
	void *ptr[5];
	ptr[0] = (void*)"makeitemvisible";
	ptr[1] = NULL;
	ptr[2] = (void*)"id";
	ptr[3] = &id;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

int MQTreeListBox::HitTestItem(int x, int y)
{
	int result = -1;
	void *ptr[9];
	ptr[0] = (void*)"hittestitem";
	ptr[1] = NULL;
	ptr[2] = (void*)"x";
	ptr[3] = &x;
	ptr[4] = (void*)"y";
	ptr[5] = &y;
	ptr[6] = (void*)"result";
	ptr[7] = &result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

void MQTreeListBox::GetItemRect(int id, int& x, int& y, int& w, int& h)
{
	void *ptr[13];
	ptr[0] = (void*)"getitemrect";
	ptr[1] = NULL;
	ptr[2] = (void*)"id";
	ptr[3] = &id;
	ptr[4] = (void*)"x";
	ptr[5] = &x;
	ptr[6] = (void*)"y";
	ptr[7] = &y;
	ptr[8] = (void*)"w";
	ptr[9] = &w;
	ptr[10] = (void*)"h";
	ptr[11] = &h;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQLabel
//---------------------------------------------------------------------------
MQLabel::MQLabel() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"label";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQLabel::MQLabel(int id) : MQWidgetBase(id)
{
}

MQLabel::~MQLabel()
{
}

std::wstring MQLabel::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQLabel::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQLabel::GetFontName()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"fontname.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"fontname";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQLabel::SetFontName(const std::wstring& value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontname";
	ptr[1] = (void*)value.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQLabel::GetFontBold()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQLabel::SetFontBold(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQLabel::GetFontColor(int& r, int& g, int& b, int& a)
{
	int value[4] = {0,0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = value[0];
	g = value[1];
	b = value[2];
	a = value[3];
}

void MQLabel::SetFontColor(int r, int g, int b, int a)
{
	int value[4] = {r,g,b,a};
	void *ptr[3];
	ptr[0] = (void*)"fontcolor.rgba";
	ptr[1] = value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQCanvasColor MQLabel::GetFontColor()
{
	MQCanvasColor c;
	GetFontColor(c.r, c.g, c.b, c.a);
	return c;
}

void MQLabel::SetFontColor(const MQCanvasColor& color)
{
	SetFontColor(color.r, color.g, color.b, color.a);
}

double MQLabel::GetFontScale()
{
	double value = 0.0;
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQLabel::SetFontScale(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQLabel::MQLabelTextAlignment MQLabel::GetAlignment()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "left") == 0) return ALIGN_LEFT;
	if(strcmp(align_str, "center") == 0) return ALIGN_CENTER;
	if(strcmp(align_str, "right") == 0) return ALIGN_RIGHT;
	return ALIGN_LEFT;
}

void MQLabel::SetAlignment(MQLabelTextAlignment value)
{
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	switch(value){
	default:
	case ALIGN_LEFT:   ptr[1] = (void*)"left"; break;
	case ALIGN_CENTER: ptr[1] = (void*)"center"; break;
	case ALIGN_RIGHT:  ptr[1] = (void*)"right"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQLabel::GetVerticalText()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"verticaltext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQLabel::SetVerticalText(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"verticaltext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQLabel::GetWordWrap()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"wordwrap";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQLabel::SetWordWrap(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"wordwrap";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQLabel::GetFrame()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"frame";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQLabel::SetFrame(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"frame";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQLabel::GetShadowText()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"shadowtext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQLabel::SetShadowText(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"shadowtext";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQLabel::SetSystemSVGFile(const wchar_t *filename)
{
	void *ptr[3];
	ptr[0] = (void*)"systemsvgfile";
	ptr[1] = (void*)filename;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQLabel::SetImageScale(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"imagescale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQLabel::GetImageScale()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"imagescale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}


//---------------------------------------------------------------------------
//  class MQEdit
//---------------------------------------------------------------------------
MQEdit::MQEdit() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"edit";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQEdit::MQEdit(int id) : MQWidgetBase(id)
{
}

MQEdit::~MQEdit()
{
}

std::wstring MQEdit::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQEdit::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQEdit::GetFontName()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"fontname.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"fontname";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQEdit::SetFontName(const std::wstring& value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontname";
	ptr[1] = (void*)value.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQEdit::GetFontBold()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetFontBold(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQEdit::GetFontScale()
{
	double value = 0.0;
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetFontScale(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQEdit::GetReadOnly()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"readonly";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetReadOnly(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"readonly";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQEdit::GetPassword()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"password";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetPassword(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"password";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQEdit::MQEditTextAlignment MQEdit::GetAlignment()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "left") == 0) return ALIGN_LEFT;
	if(strcmp(align_str, "right") == 0) return ALIGN_RIGHT;
	return ALIGN_LEFT;
}

void MQEdit::SetAlignment(MQEditTextAlignment value)
{
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	switch(value){
	default:
	case ALIGN_LEFT:   ptr[1] = (void*)"left"; break;
	case ALIGN_RIGHT:  ptr[1] = (void*)"right"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQEdit::MQEditNumericType MQEdit::GetNumeric()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"numeric";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "int") == 0) return NUMERIC_INT;
	if(strcmp(align_str, "double") == 0) return NUMERIC_DOUBLE;
	return NUMERIC_TEXT;
}

void MQEdit::SetNumeric(MQEditNumericType value)
{
	void *ptr[3];
	ptr[0] = (void*)"numeric";
	switch(value){
	default:
	case NUMERIC_TEXT:  ptr[1] = (void*)"text"; break;
	case NUMERIC_INT:   ptr[1] = (void*)"int"; break;
	case NUMERIC_DOUBLE:ptr[1] = (void*)"double"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQEdit::GetMaxLength()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"maxlength";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetMaxLength(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"maxlength";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQEdit::GetMaxAnsiLength()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"maxansilength";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetMaxAnsiLength(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"maxansilength";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQEdit::GetVisibleColumn()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"visiblecolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetVisibleColumn(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"visiblecolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQEdit::GetEnterSelect()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enterselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetEnterSelect(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enterselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQEdit::GetEnterKeyDefault()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enterkeydefault";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQEdit::SetEnterKeyDefault(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enterkeydefault";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQEdit::SetFocus(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"focus";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQEdit::SelectAll()
{
	void *ptr[3];
	ptr[0] = (void*)"selectall";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQEdit::SelectRange(size_t start, size_t end)
{
	void *ptr[7];
	ptr[0] = (void*)"selectrange";
	ptr[1] = NULL;
	ptr[2] = (void*)"start";
	ptr[3] = (void*)&start;
	ptr[4] = (void*)"end";
	ptr[5] = (void*)&end;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

bool MQEdit::GetSelectedRange(size_t& start, size_t& end)
{
	bool result = false;
	void *ptr[9];
	ptr[0] = (void*)"getselectedrange";
	ptr[1] = NULL;
	ptr[2] = (void*)"start";
	ptr[3] = (void*)&start;
	ptr[4] = (void*)"end";
	ptr[5] = (void*)&end;
	ptr[6] = (void*)"result";
	ptr[7] = (void*)&result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	return result;
}

void MQEdit::CutSelection()
{
	void *ptr[3];
	ptr[0] = (void*)"cutselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQEdit::CopySelection()
{
	void *ptr[3];
	ptr[0] = (void*)"copyselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQEdit::PasteFromClipboard()
{
	void *ptr[3];
	ptr[0] = (void*)"pastefromclipboard";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQMemo
//---------------------------------------------------------------------------
MQMemo::MQMemo() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"memo";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQMemo::MQMemo(int id) : MQWidgetBase(id)
{
}

MQMemo::~MQMemo()
{
}

void MQMemo::AddLine(const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"addline";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

std::wstring MQMemo::GetLine(int line_index)
{
	void *ptr[7];
	unsigned int length = 0;
	ptr[0] = (void*)"getline.length";
	ptr[1] = NULL;
	ptr[2] = (void*)"line";
	ptr[3] = &line_index;
	ptr[4] = (void*)"result";
	ptr[5] = &length;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"getline";
	ptr[1] = NULL;
	ptr[2] = (void*)"line";
	ptr[3] = &line_index;
	ptr[4] = (void*)"text";
	ptr[5] = buf;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

size_t MQMemo::GetTextLength()
{
	size_t length = 0;
	void *ptr[3];
	ptr[0] = (void*)"text.length_t";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return length;
}

std::wstring MQMemo::GetText()
{
	size_t length = GetTextLength();
	if(length == 0)
		return std::wstring();

	wchar_t *buf = new wchar_t[length+1];
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQMemo::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQMemo::GetFontName()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"fontname.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"fontname";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQMemo::SetFontName(const std::wstring& value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontname";
	ptr[1] = (void*)value.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetFontBold()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetFontBold(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontbold";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQMemo::GetFontScale()
{
	double value = 0.0;
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetFontScale(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"fontscale";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetReadOnly()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"readonly";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetReadOnly(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"readonly";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetPriorMenuShortcut()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"priormenushortcut";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetPriorMenuShortcut(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"priormenushortcut";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQMemo::MQBarStatus MQMemo::GetHorzBarStatus()
{
	char *status_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"horzbarstatus";
	ptr[1] = &status_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(status_str, "auto") == 0) return SCROLLBAR_AUTO;
	if(strcmp(status_str, "on") == 0) return SCROLLBAR_ON;
	if(strcmp(status_str, "off") == 0) return SCROLLBAR_OFF;
	return SCROLLBAR_AUTO;
}

void MQMemo::SetHorzBarStatus(MQBarStatus value)
{
	void *ptr[3];
	ptr[0] = (void*)"horzbarstatus";
	switch(value){
	default:
	case SCROLLBAR_AUTO: ptr[1] = (void*)"auto"; break;
	case SCROLLBAR_OFF:  ptr[1] = (void*)"off"; break;
	case SCROLLBAR_ON:   ptr[1] = (void*)"on"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQMemo::MQBarStatus MQMemo::GetVertBarStatus()
{
	char *status_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"vertbarstatus";
	ptr[1] = &status_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(status_str, "auto") == 0) return SCROLLBAR_AUTO;
	if(strcmp(status_str, "on") == 0) return SCROLLBAR_ON;
	if(strcmp(status_str, "off") == 0) return SCROLLBAR_OFF;
	return SCROLLBAR_AUTO;
}

void MQMemo::SetVertBarStatus(MQBarStatus value)
{
	void *ptr[3];
	ptr[0] = (void*)"vertbarstatus";
	switch(value){
	default:
	case SCROLLBAR_AUTO: ptr[1] = (void*)"auto"; break;
	case SCROLLBAR_OFF:  ptr[1] = (void*)"off"; break;
	case SCROLLBAR_ON:   ptr[1] = (void*)"on"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetFocus()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"focus";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetFocus(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"focus";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

size_t MQMemo::GetCaretPos()
{
	size_t value = 0;
	void *ptr[3];
	ptr[0] = (void*)"caretpos";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetCaretPos(size_t value)
{
	void *ptr[3];
	ptr[0] = (void*)"caretpos";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQMemo::GetTabColumn()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"tabcolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetTabColumn(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"tabcolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetAutoIndent()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"autoindent";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetAutoIndent(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"autoindent";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetShowTabMark()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"showtabmark";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetShowTabMark(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"showtabmark";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetShowReturnMark()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"showreturnmark";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetShowReturnMark(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"showreturnmark";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetShowLineNumber()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"showlinenumber";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetShowLineNumber(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"showlinenumber";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetSyntaxHighlight()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"syntaxhighlight";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetSyntaxHighlight(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"syntaxhighlight";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMemo::GetChanged()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"changed";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMemo::SetChanged(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"changed";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQMemo::GetMarkCharacters()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"markcharacters.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"markcharacters";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQMemo::SetMarkCharacters(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"markcharacters";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQMemo::AddSyntaxKeyword(const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"addsyntaxkeyword";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::ClearSyntaxKeyword()
{
	void *ptr[3];
	ptr[0] = (void*)"clearsyntaxkeyword";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::AddRadixPrefix(const std::wstring& prefix)
{
	void *ptr[5];
	ptr[0] = (void*)"addradixprefix";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)prefix.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::ClearRadixPrefix()
{
	void *ptr[3];
	ptr[0] = (void*)"clearradixprefix";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

std::wstring MQMemo::GetSyntaxComment() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"syntaxcomment.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"syntaxcomment";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQMemo::SetSyntaxComment(const std::wstring& word)
{
	void *ptr[3];
	ptr[0] = (void*)"syntaxcomment";
	ptr[1] = (void*)word.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQMemo::AddSyntaxMultiLineComment(const std::wstring& start, const std::wstring& end)
{
	void *ptr[7];
	ptr[0] = (void*)"addsyntaxmulitlinecomment";
	ptr[1] = NULL;
	ptr[2] = (void*)"start";
	ptr[3] = (void*)start.c_str();
	ptr[4] = (void*)"end";
	ptr[5] = (void*)end.c_str();
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::ClearSyntaxMultiLineComment()
{
	void *ptr[3];
	ptr[0] = (void*)"clearsyntaxmulitlinecomment";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::AddSyntaxString(const std::wstring& start, const std::wstring& end)
{
	void *ptr[7];
	ptr[0] = (void*)"addsyntaxstring";
	ptr[1] = NULL;
	ptr[2] = (void*)"start";
	ptr[3] = (void*)start.c_str();
	ptr[4] = (void*)"end";
	ptr[5] = (void*)end.c_str();
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::ClearSyntaxString()
{
	void *ptr[3];
	ptr[0] = (void*)"clearsyntaxstring";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::SelectAll()
{
	void *ptr[3];
	ptr[0] = (void*)"selectall";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::SelectRange(size_t start, size_t end)
{
	void *ptr[7];
	ptr[0] = (void*)"selectrange";
	ptr[1] = NULL;
	ptr[2] = (void*)"start";
	ptr[3] = (void*)&start;
	ptr[4] = (void*)"end";
	ptr[5] = (void*)&end;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

bool MQMemo::GetSelectedRange(size_t& start, size_t& end)
{
	bool result = false;
	void *ptr[9];
	ptr[0] = (void*)"getselectedrange";
	ptr[1] = NULL;
	ptr[2] = (void*)"start";
	ptr[3] = (void*)&start;
	ptr[4] = (void*)"end";
	ptr[5] = (void*)&end;
	ptr[6] = (void*)"result";
	ptr[7] = (void*)&result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	return result;
}

void MQMemo::CutSelection()
{
	void *ptr[3];
	ptr[0] = (void*)"cutselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::CopySelection()
{
	void *ptr[3];
	ptr[0] = (void*)"copyselection";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::PasteFromClipboard()
{
	void *ptr[3];
	ptr[0] = (void*)"pastefromclipboard";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::ReplaceSelectedText(const std::wstring& text)
{
	void *ptr[5];
	ptr[0] = (void*)"replaceselectedtext";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

size_t MQMemo::FindString(const std::wstring& text, size_t start_pos, bool forward, bool matchcase, bool word)
{
	size_t result = INVALID_POS;
	void *ptr[15];
	ptr[0] = (void*)"findstring";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"startpos";
	ptr[5] = (void*)&start_pos;
	ptr[6] = (void*)"forward";
	ptr[7] = (void*)&forward;
	ptr[8] = (void*)"matchcase";
	ptr[9] = (void*)&matchcase;
	ptr[10] = (void*)"word";
	ptr[11] = (void*)&word;
	ptr[12] = (void*)"result";
	ptr[13] = (void*)&result;
	ptr[14] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

size_t MQMemo::FindStringFromCaretPos(const std::wstring& text, bool forward, bool matchcase, bool word)
{
	size_t result = INVALID_POS;
	void *ptr[13];
	ptr[0] = (void*)"findstringfromcaretpos";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)text.c_str();
	ptr[4] = (void*)"forward";
	ptr[5] = (void*)&forward;
	ptr[6] = (void*)"matchcase";
	ptr[7] = (void*)&matchcase;
	ptr[8] = (void*)"word";
	ptr[9] = (void*)&word;
	ptr[10] = (void*)"result";
	ptr[11] = (void*)&result;
	ptr[12] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

size_t MQMemo::FindNextWordBreak(size_t pos, bool forward)
{
	size_t result = INVALID_POS;
	void *ptr[9];
	ptr[0] = (void*)"findnextwordbreak";
	ptr[1] = NULL;
	ptr[2] = (void*)"pos";
	ptr[3] = (void*)&pos;
	ptr[4] = (void*)"forward";
	ptr[5] = (void*)&forward;
	ptr[6] = (void*)"result";
	ptr[7] = (void*)&result;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

bool MQMemo::GetLineColumnByCaretPos(size_t pos, int& line, int& column)
{
	void *ptr[9];
	ptr[0] = (void*)"getlinecolumnbycaretpos";
	ptr[1] = NULL;
	ptr[2] = (void*)"pos";
	ptr[3] = (void*)&pos;
	ptr[4] = (void*)"line";
	ptr[5] = (void*)&line;
	ptr[6] = (void*)"column";
	ptr[7] = (void*)&column;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return (line >= 0);
}

bool MQMemo::GetCaretPosByLineColumn(int line, int column, size_t& pos)
{
	void *ptr[9];
	ptr[0] = (void*)"getcaretposbylinecolumn";
	ptr[1] = NULL;
	ptr[2] = (void*)"line";
	ptr[3] = (void*)&line;
	ptr[4] = (void*)"column";
	ptr[5] = (void*)&column;
	ptr[6] = (void*)"pos";
	ptr[7] = (void*)&pos;
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return (pos != INVALID_POS);
}

bool MQMemo::CanUndo()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"canundo";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

bool MQMemo::CanRedo()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"canredo";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

void MQMemo::Undo()
{
	void *ptr[3];
	ptr[0] = (void*)"undo";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

void MQMemo::Redo()
{
	void *ptr[3];
	ptr[0] = (void*)"redo";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQSpinBox
//---------------------------------------------------------------------------
MQSpinBox::MQSpinBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"spinbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQSpinBox::MQSpinBox(int id) : MQWidgetBase(id)
{
}

MQSpinBox::~MQSpinBox()
{
}

int MQSpinBox::GetPosition()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetPosition(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQSpinBox::GetMin()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetMin(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQSpinBox::GetMax()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetMax(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQSpinBox::GetIncrement()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"increment";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetIncrement(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"increment";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQSpinBox::MQSpinBoxTextAlignment MQSpinBox::GetAlignment()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "left") == 0) return ALIGN_LEFT;
	if(strcmp(align_str, "right") == 0) return ALIGN_RIGHT;
	return ALIGN_LEFT;
}

void MQSpinBox::SetAlignment(MQSpinBoxTextAlignment value)
{
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	switch(value){
	default:
	case ALIGN_LEFT:   ptr[1] = (void*)"left"; break;
	case ALIGN_RIGHT:  ptr[1] = (void*)"right"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQSpinBox::GetVisibleColumn()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"visiblecolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetVisibleColumn(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"visiblecolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQSpinBox::GetEnterSelect()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enterselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetEnterSelect(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enterselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQSpinBox::GetEnterKeyDefault()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enterkeydefault";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSpinBox::SetEnterKeyDefault(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enterkeydefault";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQSpinBox::SetFocus(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"focus";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQDoubleSpinBox
//---------------------------------------------------------------------------
MQDoubleSpinBox::MQDoubleSpinBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"doublespinbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQDoubleSpinBox::MQDoubleSpinBox(int id) : MQWidgetBase(id)
{
}

MQDoubleSpinBox::~MQDoubleSpinBox()
{
}

double MQDoubleSpinBox::GetPosition()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetPosition(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQDoubleSpinBox::GetMin()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetMin(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQDoubleSpinBox::GetMax()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetMax(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQDoubleSpinBox::GetIncrement()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"increment";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetIncrement(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"increment";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDoubleSpinBox::GetExponential()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"exponential";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetExponential(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"exponential";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQDoubleSpinBox::GetMantissa()
{
	double value = 0.0;
	void *ptr[3];
	ptr[0] = (void*)"mantissa";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetMantissa(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"mantissa";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQDoubleSpinBox::GetDecimalDigit()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"decimaldigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetDecimalDigit(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"decimaldigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDoubleSpinBox::GetVariableDigit()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"variabledigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetVariableDigit(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"variabledigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQDoubleSpinBox::GetAutoDigit()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"autodigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetAutoDigit(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"autodigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQDoubleSpinBox::GetMaxDecimalDigit()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"maxdecimaldigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetMaxDecimalDigit(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"maxdecimaldigit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

MQDoubleSpinBox::MQDoubleSpinBoxTextAlignment MQDoubleSpinBox::GetAlignment()
{
	char *align_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	ptr[1] = &align_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(align_str, "left") == 0) return ALIGN_LEFT;
	if(strcmp(align_str, "right") == 0) return ALIGN_RIGHT;
	return ALIGN_LEFT;
}

void MQDoubleSpinBox::SetAlignment(MQDoubleSpinBoxTextAlignment value)
{
	void *ptr[3];
	ptr[0] = (void*)"alignment";
	switch(value){
	default:
	case ALIGN_LEFT:   ptr[1] = (void*)"left"; break;
	case ALIGN_RIGHT:  ptr[1] = (void*)"right"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQDoubleSpinBox::GetVisibleColumn()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"visiblecolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetVisibleColumn(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"visiblecolumn";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDoubleSpinBox::GetEnterSelect()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enterselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetEnterSelect(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enterselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDoubleSpinBox::GetEnterKeyDefault()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"enterkeydefault";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQDoubleSpinBox::SetEnterKeyDefault(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"enterkeydefault";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQDoubleSpinBox::SetDisplayUnit(MQDISPLAYUNIT unit)
{
	int value = (int)unit;
	void *ptr[3];
	ptr[0] = (void*)"unit";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQDoubleSpinBox::SetFocus(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"focus";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQSlider
//---------------------------------------------------------------------------
MQSlider::MQSlider() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"slider";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQSlider::MQSlider(int id) : MQWidgetBase(id)
{
}

MQSlider::~MQSlider()
{
}

double MQSlider::GetPosition()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSlider::SetPosition(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQSlider::GetMin()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSlider::SetMin(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQSlider::GetMax()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQSlider::SetMax(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQProgressBar
//---------------------------------------------------------------------------
MQProgressBar::MQProgressBar() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"progressbar";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQProgressBar::MQProgressBar(int id) : MQWidgetBase(id)
{
}

MQProgressBar::~MQProgressBar()
{
}

double MQProgressBar::GetPosition()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQProgressBar::SetPosition(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQProgressBar::GetMin()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQProgressBar::SetMin(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

double MQProgressBar::GetMax()
{
	double value = 0;
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQProgressBar::SetMax(double value)
{
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQScrollBar
//---------------------------------------------------------------------------
MQScrollBar::MQScrollBar() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"scrollbar";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQScrollBar::MQScrollBar(int id) : MQWidgetBase(id)
{
}

MQScrollBar::~MQScrollBar()
{
}

MQScrollBar::MQScrollBarDirection MQScrollBar::GetDirection()
{
	char *dir_str = NULL;
	void *ptr[3];
	ptr[0] = (void*)"direction";
	ptr[1] = &dir_str;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(strcmp(dir_str, "horz") == 0) return DIRECTION_HORIZONTAL;
	if(strcmp(dir_str, "vert") == 0) return DIRECTION_VERTICAL;
	return DIRECTION_HORIZONTAL;
}

void MQScrollBar::SetDirection(MQScrollBarDirection value)
{
	void *ptr[3];
	ptr[0] = (void*)"direction";
	switch(value){
	default:
	case DIRECTION_HORIZONTAL:ptr[1] = (void*)"horz"; break;
	case DIRECTION_VERTICAL:  ptr[1] = (void*)"vert"; break;
	}
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQScrollBar::GetPosition()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQScrollBar::SetPosition(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"position";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQScrollBar::GetMin()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQScrollBar::SetMin(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"min";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQScrollBar::GetMax()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQScrollBar::SetMax(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"max";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQScrollBar::GetPage()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"page";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQScrollBar::SetPage(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"page";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQScrollBar::GetIncrement()
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"increment";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQScrollBar::SetIncrement(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"increment";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQColorPanel
//---------------------------------------------------------------------------
MQColorPanel::MQColorPanel() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"colorpanel";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQColorPanel::MQColorPanel(int id) : MQWidgetBase(id)
{
}

MQColorPanel::~MQColorPanel()
{
}

void MQColorPanel::GetColor(int& r, int& g, int& b)
{
	int array[3] = {0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"rgb";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
}

void MQColorPanel::SetColor(int r, int g, int b)
{
	int array[3] = {r,g,b};
	void *ptr[7];
	ptr[0] = (void*)"rgb";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQColorPanel::GetHSV(double& h, double& s, double& v)
{
	double array[3] = {0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"hsv";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	h = array[0];
	s = array[1];
	v = array[2];
}

void MQColorPanel::SetHSV(double h, double s, double v)
{
	double array[3] = {h,s,v};
	void *ptr[3];
	ptr[0] = (void*)"hsv";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQPaintBox
//---------------------------------------------------------------------------
MQPaintBox::MQPaintBox() : MQWidgetBase()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"paintbox";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQPaintBox::MQPaintBox(int id) : MQWidgetBase(id)
{
}

MQPaintBox::~MQPaintBox()
{
}


//---------------------------------------------------------------------------
//  class MQMenuBar
//---------------------------------------------------------------------------
MQMenuBar::MQMenuBar(MQWidgetBase *parent) : MQFrameBase()
{
	int parentID = (parent != NULL) ? parent->GetID() : NullID;

	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"menubar";
	ptr[2] = (void*)"parent";
	ptr[3] = &parentID;
	ptr[4] = (void*)"id";
	ptr[5] = &m_ID;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQMenuBar::MQMenuBar(int id) : MQFrameBase(id)
{
}

MQMenuBar::~MQMenuBar()
{
	std::set<MQMenuItem*>::iterator it;
	for(it = m_CreatedMenuItems.begin(); it != m_CreatedMenuItems.end(); ){
		delete *it;
		it = m_CreatedMenuItems.erase(it);
	}
}

MQMenuItem *MQMenuBar::CreateMenuItem(const std::wstring& text)
{
	MQMenuItem *p = new MQMenuItem(this);
	m_CreatedMenuItems.insert(p);
	p->SetText(text);
	return p;
}

MQMenuItem *MQMenuBar::CreateSubMenuItem(MQMenuItem *parent, const std::wstring& text)
{
	MQMenuItem *p = new MQMenuItem(parent);
	m_CreatedMenuItems.insert(p);
	p->SetText(text);
	return p;
}


//---------------------------------------------------------------------------
//  class MQMenuItem
//---------------------------------------------------------------------------
MQMenuItem::MQMenuItem(MQWidgetBase *parent) : MQWidgetBase()
{
	int parentID = (parent != NULL) ? parent->GetID() : NullID;

	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"menuitem";
	ptr[2] = (void*)"parent";
	ptr[3] = &parentID;
	ptr[4] = (void*)"id";
	ptr[5] = &m_ID;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQMenuItem::MQMenuItem(int id) : MQWidgetBase(id)
{
}

MQMenuItem::~MQMenuItem()
{
}

std::wstring MQMenuItem::GetText()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"text.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQMenuItem::SetText(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"text";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMenuItem::GetChecked()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"checked";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMenuItem::SetChecked(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"checked";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMenuItem::GetToggle()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"toggle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMenuItem::SetToggle(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"toggle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMenuItem::GetClickClose()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"clickclose";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMenuItem::SetClickClose(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"clickclose";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQMenuItem::GetSeparator()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"separator";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQMenuItem::SetSeparator(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"separator";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQMenuItem::GetShortcutString()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"shortcutstring.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"text";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQMenuItem::SetShortcutString(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"shortcutstring";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQMenuItem::SetSystemSVGFile(const wchar_t *filename)
{
	void *ptr[3];
	ptr[0] = (void*)"systemsvgfile";
	ptr[1] = (void*)filename;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQMenuItem::SetRightIconSystemSVGFile(const wchar_t *filename)
{
	void *ptr[3];
	ptr[0] = (void*)"righticonsvgfile";
	ptr[1] = (void*)filename;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQWindowBase
//---------------------------------------------------------------------------
MQWindowBase::MQWindowBase() : MQWidgetBase()
{
}

MQWindowBase::MQWindowBase(int id) : MQWidgetBase(id)
{
}

MQWindowBase::~MQWindowBase()
{
	std::set<MQWidgetBase*>::iterator it;
	for(it = m_CreatedWidgets.begin(); it != m_CreatedWidgets.end(); ){
		delete *it;
		it = m_CreatedWidgets.erase(it);
	}
}

void MQWindowBase::AddChildWindow(MQWindowBase *child)
{
	if(child == NULL) return;

	void *ptr[5];
	int child_id = child->GetID();
	int result = -1;

	ptr[0] = (void*)"child";
	ptr[1] = &child_id;
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_ADD_CHILD_WINDOW, (void*)ptr);
}

void MQWindowBase::RemoveChildWindow(MQWindowBase *child)
{
	if(child == NULL) return;

	void *ptr[5];
	int child_id = child->GetID();
	int result = -1;

	ptr[0] = (void*)"child";
	ptr[1] = &child_id;
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_REMOVE_CHILD_WINDOW, (void*)ptr);
}

MQFrame *MQWindowBase::CreateHorizontalFrame(MQWidgetBase *parent)
{
	MQFrame *p = new MQFrame();
	m_CreatedWidgets.insert(p);
	p->SetAlignment(MQFrame::ALIGN_HORIZONTAL);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQFrame *MQWindowBase::CreateVerticalFrame(MQWidgetBase *parent)
{
	MQFrame *p = new MQFrame();
	m_CreatedWidgets.insert(p);
	p->SetAlignment(MQFrame::ALIGN_VERTICAL);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQDockFrame *MQWindowBase::CreateDockFrame(MQWidgetBase *parent)
{
	MQDockFrame *p = new MQDockFrame();
	m_CreatedWidgets.insert(p);
	p->SetAlignment(MQFrame::ALIGN_VERTICAL);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQGroupBox *MQWindowBase::CreateGroupBox(MQWidgetBase *parent, const std::wstring& str)
{
	MQGroupBox *p = new MQGroupBox();
	m_CreatedWidgets.insert(p);
	p->SetText(str);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQTab *MQWindowBase::CreateTab(MQWidgetBase *parent)
{
	MQTab *p = new MQTab();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQButton *MQWindowBase::CreateButton(MQWidgetBase *parent, const std::wstring& str)
{
	MQButton *p = new MQButton();
	m_CreatedWidgets.insert(p);
	p->SetText(str);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQCheckBox *MQWindowBase::CreateCheckBox(MQWidgetBase *parent, const std::wstring& str)
{
	MQCheckBox *p = new MQCheckBox();
	m_CreatedWidgets.insert(p);
	p->SetText(str);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQRadioButton *MQWindowBase::CreateRadioButton(MQWidgetBase *parent, const std::wstring& str)
{
	MQRadioButton *p = new MQRadioButton();
	m_CreatedWidgets.insert(p);
	p->SetText(str);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQComboBox *MQWindowBase::CreateComboBox(MQWidgetBase *parent)
{
	MQComboBox *p = new MQComboBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQListBox *MQWindowBase::CreateListBox(MQWidgetBase *parent)
{
	MQListBox *p = new MQListBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQCheckListBox *MQWindowBase::CreateCheckListBox(MQWidgetBase *parent)
{
	MQCheckListBox *p = new MQCheckListBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQTreeListBox *MQWindowBase::CreateTreeListBox(MQWidgetBase *parent)
{
	MQTreeListBox *p = new MQTreeListBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQLabel *MQWindowBase::CreateLabel(MQWidgetBase *parent, const std::wstring& str)
{
	MQLabel *p = new MQLabel();
	m_CreatedWidgets.insert(p);
	p->SetText(str);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQEdit *MQWindowBase::CreateEdit(MQWidgetBase *parent, const std::wstring& str)
{
	MQEdit *p = new MQEdit();
	m_CreatedWidgets.insert(p);
	p->SetText(str);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQMemo *MQWindowBase::CreateMemo(MQWidgetBase *parent)
{
	MQMemo *p = new MQMemo();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQSpinBox *MQWindowBase::CreateSpinBox(MQWidgetBase *parent)
{
	MQSpinBox *p = new MQSpinBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQDoubleSpinBox *MQWindowBase::CreateDoubleSpinBox(MQWidgetBase *parent)
{
	MQDoubleSpinBox *p = new MQDoubleSpinBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQSlider *MQWindowBase::CreateSlider(MQWidgetBase *parent)
{
	MQSlider *p = new MQSlider();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQProgressBar *MQWindowBase::CreateProgressBar(MQWidgetBase *parent)
{
	MQProgressBar *p = new MQProgressBar();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQScrollBar *MQWindowBase::CreateScrollBar(MQWidgetBase *parent)
{
	MQScrollBar *p = new MQScrollBar();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQScrollBox *MQWindowBase::CreateScrollBox(MQWidgetBase *parent)
{
	MQScrollBox *p = new MQScrollBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQColorPanel *MQWindowBase::CreateColorPanel(MQWidgetBase *parent)
{
	MQColorPanel *p = new MQColorPanel();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQPaintBox *MQWindowBase::CreatePaintBox(MQWidgetBase *parent)
{
	MQPaintBox *p = new MQPaintBox();
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

MQMenuBar *MQWindowBase::CreateMenuBar(MQWidgetBase *parent)
{
	MQMenuBar *p = new MQMenuBar(parent);
	m_CreatedWidgets.insert(p);
	if(parent != NULL){
		parent->AddChild(p);
	}
	return p;
}

void MQWindowBase::DeleteWidget(MQWidgetBase *widget)
{
	assert(widget != NULL);
	if(widget == NULL) return;

	m_CreatedWidgets.erase(widget);

	delete widget;
}

// Set this window as a modal window.
void MQWindowBase::SetModal()
{
	void *ptr[3];
	ptr[0] = (void*)"setmodal";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

// Release a modal status.
void MQWindowBase::ReleaseModal()
{
	void *ptr[3];
	ptr[0] = (void*)"releasemodal";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

// Check if this window has a modal status.
bool MQWindowBase::IsModal()
{
	bool result = false;

	void *ptr[5];
	ptr[0] = (void*)"ismodal";
	ptr[1] = NULL;
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);

	return result;
}

std::wstring MQWindowBase::GetTitle()
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"title.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"title";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQWindowBase::SetTitle(const std::wstring& text)
{
	void *ptr[3];
	ptr[0] = (void*)"title";
	ptr[1] = (void*)text.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQWindowBase::GetPosX() const
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"pos_x";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetPosX(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"pos_x";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQWindowBase::GetPosY() const
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"pos_y";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetPosY(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"pos_y";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetWindowFrame() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"windowframe";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetWindowFrame(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"windowframe";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetTitleBar() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"titlebar";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetTitleBar(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"titlebar";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetCanResize() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"canresize";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetCanResize(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"canresize";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetCloseButton() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"closebutton";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetCloseButton(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"closebutton";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetMaximizeButton() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"maximizebutton";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetMaximizeButton(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"maximizebutton";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetMinimizeButton() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"minimizebutton";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetMinimizeButton(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"minimizebutton";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetMaximized() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"maximized";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetMaximized(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"maximized";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetMinimized() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"minimized";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetMinimized(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"minimized";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQWindowBase::GetBackColor(int& r, int& g, int& b) const
{
	int array[3] = {0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"backcolor.rgb";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
}

MQCanvasColor MQWindowBase::GetBackColor() const
{
	MQCanvasColor col;
	GetBackColor(col.r, col.g, col.b);
	return col;
}

void MQWindowBase::SetBackColor(int r, int g, int b)
{
	int array[3] = {r,g,b};
	void *ptr[9];
	ptr[0] = (void*)"backcolor.rgb";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQWindowBase::SetBackColor(MQCanvasColor col)
{
	SetBackColor(col.r, col.g, col.b);
}

int MQWindowBase::GetAlphaBlend() const
{
	int value = 255;
	void *ptr[3];
	ptr[0] = (void*)"alphablend";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetAlphaBlend(int value)
{
	void *ptr[3];
	ptr[0] = (void*)"alphablend";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::GetAcceptDrops() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"acceptdrops";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQWindowBase::SetAcceptDrops(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"acceptdrops";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQWindowBase::ExecuteMenuShortcut(MQWidgetKeyParam& param)
{
	DWORD button_state = 0;
	int auto_repeat = param.AutoRepeat ? 1 : 0;
	if(param.LButton) button_state |= MK_LBUTTON;
	if(param.MButton) button_state |= MK_MBUTTON;
	if(param.RButton) button_state |= MK_RBUTTON;
	if(param.Shift) button_state |= MK_SHIFT;
	if(param.Ctrl) button_state |= MK_CONTROL;
	if(param.Alt) button_state |= MK_ALT;

	void *ptr[11];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"executemenushortcut";
	ptr[2] = (void*)"key";
	ptr[3] = &param.Key;
	ptr[4] = (void*)"button_state";
	ptr[5] = &button_state;
	ptr[6] = (void*)"auto_repeat";
	ptr[7] = &auto_repeat;
	ptr[8] = (void*)"finished";
	ptr[9] = &param.Finished;
	ptr[10] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);
	return param.Finished;
}


//---------------------------------------------------------------------------
//  class MQWindow
//---------------------------------------------------------------------------
MQWindow::MQWindow() : MQWindowBase()
{
	CreateWindowID();
}

MQWindow::MQWindow(int id) : MQWindowBase(id)
{
}

MQWindow::MQWindow(MQWindowBase& parent) : MQWindowBase()
{
	CreateWindowID();
	parent.AddChildWindow(this);
}

MQWindow::~MQWindow()
{
}

void MQWindow::CreateWindowID()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"window";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQWindow MQWindow::GetMainWindow()
{
	int id = GetSystemWidgetID(MQSystemWidget::MainWindow);
	return MQWindow(id);
}

MQWindow *MQWindow::CreateWindow(MQWindowBase& parent)
{
	return new MQWindow(parent);
}

//---------------------------------------------------------------------------
//  class MQDockWindow
//---------------------------------------------------------------------------
MQDockWindow::MQDockWindow() : MQWindowBase()
{
	CreateWindowID();
}

MQDockWindow::MQDockWindow(int id) : MQWindowBase(id)
{
}

MQDockWindow::MQDockWindow(MQWindowBase& parent) : MQWindowBase()
{
	CreateWindowID();
	parent.AddChildWindow(this);
}

MQDockWindow::~MQDockWindow()
{
}

void MQDockWindow::EnableDockableMenu()
{
	bool value = true;
	void *ptr[3];
	ptr[0] = (void*)"dockablemenu";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDockWindow::GetCanDock()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"candock";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

void MQDockWindow::SetCanDock(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"candock";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDockWindow::GetShowDockingTitle()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"showdockingtitle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

void MQDockWindow::SetShowDockingTitle(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"showdockingtitle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDockWindow::GetVerticalTitle()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"verticaltitle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

void MQDockWindow::SetVerticalTitle(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"verticaltitle";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQDockWindow::IsDocking()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"docking";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

void MQDockWindow::DockToFrame(MQDockFrame *frame, MQDockWindow *hierarchy_parent, MQDockDirection direction)
{
	int frameID = (frame != nullptr) ? frame->GetID() : NullID;
	int parentID = (hierarchy_parent != nullptr) ? hierarchy_parent->GetID() : NullID;
	void *ptr[9];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"docktoframe";
	ptr[2] = (void*)"frame";
	ptr[3] = &frameID;
	ptr[4] = (void*)"hierarchy_parent";
	ptr[5] = &parentID;
	ptr[6] = (void*)"direction";
	switch(direction){
	case DOCK_NONE: default: ptr[7] = (void*)""; break;
	case DOCK_LEFT: ptr[7] = (void*)"left"; break;
	case DOCK_RIGHT: ptr[7] = (void*)"right"; break;
	case DOCK_TOP: ptr[7] = (void*)"top"; break;
	case DOCK_BOTTOM: ptr[7] = (void*)"bottom"; break;
	}
	ptr[8] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);
}

void MQDockWindow::RedockWithJustSize()
{
	void *ptr[3];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"redockwithjustsize";
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);
}

void MQDockWindow::CreateWindowID()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"dockwindow";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQDockWindow *MQDockWindow::CreateDockWindow(MQWindowBase& parent)
{
	return new MQDockWindow(parent);
}

//---------------------------------------------------------------------------
//  class MQDialog
//---------------------------------------------------------------------------
MQDialog::MQDialog() : MQWindowBase()
{
	CreateDialogID();
}

MQDialog::MQDialog(int id) : MQWindowBase(id)
{
}

MQDialog::MQDialog(MQWindowBase& parent) : MQWindowBase()
{
	CreateDialogID();
	parent.AddChildWindow(this);
}

MQDialog::MQDialog(MQWindowBase& parent, int dummy_for_no_creation) : MQWindowBase()
{
}

MQDialog::~MQDialog()
{
}

void MQDialog::CreateDialogID()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"dialog";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQDialog::DIALOG_RESULT MQDialog::Execute()
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;

	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"modal";
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

void MQDialog::Close(DIALOG_RESULT code)
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"close";
	ptr[2] = (void*)"code";
	switch(code){
	case DIALOG_OK: ptr[3] = (void*)"ok"; break;
	case DIALOG_CANCEL: ptr[3] = (void*)"cancel"; break;
	case DIALOG_YES: ptr[3] = (void*)"yes"; break;
	case DIALOG_NO: ptr[3] = (void*)"no"; break;
	case DIALOG_ALL: ptr[3] = (void*)"all"; break;
	default: ptr[3] = (void*)"none"; break;
	}
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);
}

MQDialog::DIALOG_RESULT MQDialog::MessageWarningBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title)
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;
	int parent_id = parent.GetID();

	void *ptr[13];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"messagebox";
	ptr[2] = (void*)"messagetype";
	ptr[3] = (void*)"warning";
	ptr[4] = (void*)"parent";
	ptr[5] = &parent_id;
	ptr[6] = (void*)"message";
	ptr[7] = (void*)message.c_str();
	ptr[8] = (void*)"title";
	ptr[9] = (void*)title.c_str();
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

MQDialog::DIALOG_RESULT MQDialog::MessageInformationBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title)
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;
	int parent_id = parent.GetID();

	void *ptr[13];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"messagebox";
	ptr[2] = (void*)"messagetype";
	ptr[3] = (void*)"information";
	ptr[4] = (void*)"parent";
	ptr[5] = &parent_id;
	ptr[6] = (void*)"message";
	ptr[7] = (void*)message.c_str();
	ptr[8] = (void*)"title";
	ptr[9] = (void*)title.c_str();
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

MQDialog::DIALOG_RESULT MQDialog::MessageYesNoBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title)
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;
	int parent_id = parent.GetID();

	void *ptr[13];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"messagebox";
	ptr[2] = (void*)"messagetype";
	ptr[3] = (void*)"yesno";
	ptr[4] = (void*)"parent";
	ptr[5] = &parent_id;
	ptr[6] = (void*)"message";
	ptr[7] = (void*)message.c_str();
	ptr[8] = (void*)"title";
	ptr[9] = (void*)title.c_str();
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

MQDialog::DIALOG_RESULT MQDialog::MessageYesNoCancelBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title)
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;
	int parent_id = parent.GetID();

	void *ptr[13];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"messagebox";
	ptr[2] = (void*)"messagetype";
	ptr[3] = (void*)"yesnocancel";
	ptr[4] = (void*)"parent";
	ptr[5] = &parent_id;
	ptr[6] = (void*)"message";
	ptr[7] = (void*)message.c_str();
	ptr[8] = (void*)"title";
	ptr[9] = (void*)title.c_str();
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

MQDialog::DIALOG_RESULT MQDialog::MessageOkCancelBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title)
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;
	int parent_id = parent.GetID();

	void *ptr[13];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"messagebox";
	ptr[2] = (void*)"messagetype";
	ptr[3] = (void*)"okcancel";
	ptr[4] = (void*)"parent";
	ptr[5] = &parent_id;
	ptr[6] = (void*)"message";
	ptr[7] = (void*)message.c_str();
	ptr[8] = (void*)"title";
	ptr[9] = (void*)title.c_str();
	ptr[10] = (void*)"result";
	ptr[11] = &result;
	ptr[12] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

MQDialog::DIALOG_RESULT MQDialog::MessageBox(MQWindowBase& parent, const std::wstring& message, const std::wstring& title, const std::vector<DIALOG_RESULT>& buttons, int default_index)
{
	MQDialog::DIALOG_RESULT result = MQDialog::DIALOG_NONE;
	int parent_id = parent.GetID();
	std::string button_str;
	for(size_t n=0; n<buttons.size(); n++){
		if(n != 0) button_str += ";";
		switch(buttons[n]){
		case DIALOG_NONE: default: break;
		case DIALOG_OK: button_str += "ok"; break;
		case DIALOG_CANCEL: button_str += "cancel"; break;
		case DIALOG_YES: button_str += "yes"; break;
		case DIALOG_NO: button_str += "no"; break;
		case DIALOG_ALL: button_str += "all"; break;
		}
	}
	void *ptr[15];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"messagebox";
	ptr[2] = (void*)"messagetype";
	ptr[3] = (void*)"buttons";
	ptr[4] = (void*)"parent";
	ptr[5] = &parent_id;
	ptr[6] = (void*)"message";
	ptr[7] = (void*)message.c_str();
	ptr[8] = (void*)"title";
	ptr[9] = (void*)title.c_str();
	ptr[10] = (void*)"buttons";
	ptr[11] = (void*)button_str.c_str();
	ptr[12] = (void*)"defaultindex";
	ptr[13] = &default_index;
	ptr[14] = NULL;
	MQWidget_Value(NullID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}


//---------------------------------------------------------------------------
//  class MQPopup
//---------------------------------------------------------------------------
MQPopup::MQPopup() : MQWindowBase()
{
	CreatePopupID();
}

MQPopup::MQPopup(int id) : MQWindowBase(id)
{
}

MQPopup::MQPopup(MQWindowBase& parent) : MQWindowBase()
{
	CreatePopupID();
	parent.AddChildWindow(this);
}

MQPopup::~MQPopup()
{
	std::set<MQMenuItem*>::iterator it;
	for(it = m_CreatedMenuItems.begin(); it != m_CreatedMenuItems.end(); ){
		delete *it;
		it = m_CreatedMenuItems.erase(it);
	}
}

void MQPopup::CreatePopupID()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"popup";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

MQMenuItem *MQPopup::CreateMenuItem(const std::wstring& text)
{
	MQMenuItem *p = new MQMenuItem(this);
	m_CreatedMenuItems.insert(p);
	p->SetText(text);
	return p;
}

MQMenuItem *MQPopup::CreateSubMenuItem(MQMenuItem *parent, const std::wstring& text)
{
	MQMenuItem *p = new MQMenuItem(parent);
	m_CreatedMenuItems.insert(p);
	p->SetText(text);
	return p;
}

void MQPopup::GetPreferredSidePosition(int& x, int& y, int& w, int& h, MQWidgetBase *widget, bool horz)
{
	int widgetID = (widget != NULL) ? widget->GetID() : NullID;
	int values[4] = {0, 0, 0, 0};
	
	void *args[7];
	args[0] = (void*)"rect";
	args[1] = values;
	args[2] = (void*)"widget";
	args[3] = &widgetID;
	args[4] = (void*)"horz";
	args[5] = &horz;
	args[6] = NULL;
	
	void *ptr[3];
	ptr[0] = (void*)"prefsidepos";
	ptr[1] = args;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	x = values[0];
	y = values[1];
	w = values[2];
	h = values[3];
}

void MQPopup::ShowPopup(int screen_x, int screen_y)
{
	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"popup";
	ptr[2] = (void*)"screen_x";
	ptr[3] = &screen_x;
	ptr[4] = (void*)"screen_y";
	ptr[5] = &screen_y;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);
}

bool MQPopup::GetShadow()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"shadow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQPopup::SetShadow(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"shadow";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQPopup::GetOverlay()
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"overlay";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQPopup::SetOverlay(bool value)
{
	void *ptr[3];
	ptr[0] = (void*)"overlay";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQColorDialog
//---------------------------------------------------------------------------
MQColorDialog::MQColorDialog(MQWindowBase& parent) : MQDialog(parent, 0)
{
	CreateColorDialogID();
	parent.AddChildWindow(this);
}

MQColorDialog::~MQColorDialog()
{
}

void MQColorDialog::CreateColorDialogID()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"colordialog";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		m_IDOwner = true;
		RegisterID();
	}
}

void MQColorDialog::GetColor(int& r, int& g, int& b)
{
	int array[3] = {0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"rgb";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	r = array[0];
	g = array[1];
	b = array[2];
}

void MQColorDialog::SetColor(int r, int g, int b)
{
	int array[3] = {r,g,b};
	void *ptr[7];
	ptr[0] = (void*)"rgb";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQColorDialog::GetHSV(double& h, double& s, double& v)
{
	double array[3] = {0,0,0};
	void *ptr[3];
	ptr[0] = (void*)"hsv";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	h = array[0];
	s = array[1];
	v = array[2];
}

void MQColorDialog::SetHSV(double h, double s, double v)
{
	double array[3] = {h,s,v};
	void *ptr[3];
	ptr[0] = (void*)"hsv";
	ptr[1] = array;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQFileDialogBase
//---------------------------------------------------------------------------
MQFileDialogBase::MQFileDialogBase()
{
	m_ID = NullID;
}

MQFileDialogBase::~MQFileDialogBase()
{
	if(m_ID != NullID){
		//s_WidgetIDMap.erase(m_ID);

		void *ptr[1];
		ptr[0] = NULL;
		MQWidget_Value(m_ID, MQWIDGET_DELETE, (void*)ptr);

		m_ID = NullID;
	}
}

int MQFileDialogBase::AddFilter(const std::wstring& val)
{
	int result = -1;
	void *ptr[7];
	ptr[0] = (void*)"addfilter";
	ptr[1] = NULL;
	ptr[2] = (void*)"text";
	ptr[3] = (void*)val.c_str();
	ptr[4] = (void*)"result";
	ptr[5] = &result;
	ptr[6] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
	return result;
}

int MQFileDialogBase::GetFilterCount() const
{
	int value = 0;
	void *ptr[3];

	ptr[0] = (void*)"filter.count";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

std::wstring MQFileDialogBase::GetFilter(int index) const
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"filter.text.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"filter.text";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFileDialogBase::SetFilter(int index, const std::wstring& val)
{
	void *ptr[5];
	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"filter.text";
	ptr[3] = (void*)val.c_str();
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

void MQFileDialogBase::ClearFilters()
{
	void *ptr[3];
	ptr[0] = (void*)"clearfilters";
	ptr[1] = NULL;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EDIT, (void*)ptr);
}

std::wstring MQFileDialogBase::GetTitle() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"title.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"title";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFileDialogBase::SetTitle(const std::wstring& val)
{
	void *ptr[3];
	ptr[0] = (void*)"title";
	ptr[1] = (void*)val.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQFileDialogBase::GetFileName() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"filename.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"filename";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFileDialogBase::SetFileName(const std::wstring& val)
{
	void *ptr[3];
	ptr[0] = (void*)"filename";
	ptr[1] = (void*)val.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQFileDialogBase::GetInitialDir() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"initialdir.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"initialdir";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFileDialogBase::SetInitialDir(const std::wstring& val)
{
	void *ptr[3];
	ptr[0] = (void*)"initialdir";
	ptr[1] = (void*)val.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQFileDialogBase::GetDefaultExt() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"defaultext.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"defaultext";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFileDialogBase::SetDefaultExt(const std::wstring& val)
{
	void *ptr[3];
	ptr[0] = (void*)"defaultext";
	ptr[1] = (void*)val.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

int MQFileDialogBase::GetFilterIndex() const
{
	int value = 0;
	void *ptr[3];
	ptr[0] = (void*)"filterindex";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFileDialogBase::SetFilterIndex(int val)
{
	void *ptr[3];
	ptr[0] = (void*)"filterindex";
	ptr[1] = &val;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQFileDialogBase::GetNoChangeDir() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"nochangedir";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFileDialogBase::SetNoChangeDir(bool val)
{
	void *ptr[3];
	ptr[0] = (void*)"nochangedir";
	ptr[1] = &val;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}


//---------------------------------------------------------------------------
//  class MQOpenFileDialog
//---------------------------------------------------------------------------
MQOpenFileDialog::MQOpenFileDialog(MQWindowBase& parent) : MQFileDialogBase()
{
	int parentID = parent.GetID();

	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"openfiledialog";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = (void*)"parent";
	ptr[5] = &parentID;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		//RegisterID();
	}
}

MQOpenFileDialog::~MQOpenFileDialog()
{
}

bool MQOpenFileDialog::GetFileMustExist() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"filemustexist";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQOpenFileDialog::SetFileMustExist(bool val)
{
	void *ptr[3];
	ptr[0] = (void*)"filemustexist";
	ptr[1] = &val;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQOpenFileDialog::GetMultiSelect() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQOpenFileDialog::SetMultiSelect(bool val)
{
	void *ptr[3];
	ptr[0] = (void*)"multiselect";
	ptr[1] = &val;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQOpenFileDialog::Execute()
{
	bool result = false;

	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"fileopen";
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}

int MQOpenFileDialog::GetFileNamesCount() const
{
	int value = 0;
	void *ptr[3];

	ptr[0] = (void*)"filenames.count";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);
	return value;
}

std::wstring MQOpenFileDialog::GetFileNames(int index) const
{
	void *ptr[5];
	unsigned int length = 0;

	ptr[0] = (void*)"index";
	ptr[1] = &index;
	ptr[2] = (void*)"filenames.length";
	ptr[3] = &length;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[2] = (void*)"filenames";
	ptr[3] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}


//---------------------------------------------------------------------------
//  class MQSaveFileDialog
//---------------------------------------------------------------------------
MQSaveFileDialog::MQSaveFileDialog(MQWindowBase& parent) : MQFileDialogBase()
{
	int parentID = parent.GetID();

	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"savefiledialog";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = (void*)"parent";
	ptr[5] = &parentID;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		//RegisterID();
	}
}

MQSaveFileDialog::~MQSaveFileDialog()
{
}

bool MQSaveFileDialog::Execute()
{
	bool result = false;

	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"filesave";
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}


//---------------------------------------------------------------------------
//  class MQFolderDialog
//---------------------------------------------------------------------------
MQFolderDialog::MQFolderDialog(MQWindowBase& parent)
	: m_ID(NullID)
{
	int parentID = parent.GetID();

	void *ptr[7];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"folderdialog";
	ptr[2] = (void*)"id";
	ptr[3] = &m_ID;
	ptr[4] = (void*)"parent";
	ptr[5] = &parentID;
	ptr[6] = NULL;
	MQWidget_Value(NullID, MQWIDGET_CREATE, (void*)ptr);

	if(m_ID != NullID){
		//RegisterID();
	}
}

MQFolderDialog::~MQFolderDialog()
{
	if(m_ID != NullID){
		//s_WidgetIDMap.erase(m_ID);

		void *ptr[1];
		ptr[0] = NULL;
		MQWidget_Value(m_ID, MQWIDGET_DELETE, (void*)ptr);

		m_ID = NullID;
	}
}

std::wstring MQFolderDialog::GetTitle() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"title.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"title";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFolderDialog::SetTitle(const std::wstring& val)
{
	void *ptr[3];
	ptr[0] = (void*)"title";
	ptr[1] = (void*)val.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

std::wstring MQFolderDialog::GetFolder() const
{
	void *ptr[3];
	unsigned int length = 0;

	ptr[0] = (void*)"folder.length";
	ptr[1] = &length;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	if(length == 0){
		return std::wstring();
	}

	wchar_t *buf = new wchar_t[length+1];
	ptr[0] = (void*)"folder";
	ptr[1] = buf;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	std::wstring ret(buf);
	delete[] buf;
	return ret;
}

void MQFolderDialog::SetFolder(const std::wstring& val)
{
	void *ptr[3];
	ptr[0] = (void*)"folder";
	ptr[1] = (void*)val.c_str();
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQFolderDialog::GetNewFolder() const
{
	bool value = false;
	void *ptr[3];
	ptr[0] = (void*)"newfolder";
	ptr[1] = &value;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_GET, (void*)ptr);

	return value;
}

void MQFolderDialog::SetNewFolder(bool val)
{
	void *ptr[3];
	ptr[0] = (void*)"newfolder";
	ptr[1] = &val;
	ptr[2] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_SET, (void*)ptr);
}

bool MQFolderDialog::Execute()
{
	bool result = false;

	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"folder";
	ptr[2] = (void*)"result";
	ptr[3] = &result;
	ptr[4] = NULL;
	MQWidget_Value(m_ID, MQWIDGET_EXECUTE, (void*)ptr);

	return result;
}


//---------------------------------------------------------------------------
//  class MQSVGDraw
//---------------------------------------------------------------------------
MQSVGDraw::MQSVGDraw()
{
	void *ptr[5];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"svg";
	ptr[2] = (void*)"ptr";
	ptr[3] = (void*)&m_Ptr;
	ptr[4] = NULL;
	MQSVGDraw_Value(nullptr, MQWIDGET_CREATE, (void*)ptr);
}

MQSVGDraw::~MQSVGDraw()
{
	void *ptr[1];
	ptr[0] = NULL;
	MQSVGDraw_Value(m_Ptr, MQWIDGET_DELETE, (void*)ptr);
}

bool MQSVGDraw::LoadFile(const wchar_t *filename)
{
	int result = 0;
	void *ptr[6];
	ptr[0] = (void*)"load";
	ptr[1] = (void*)"file";
	ptr[2] = (void*)filename;
	ptr[3] = (void*)"result";
	ptr[4] = (void*)&result;
	ptr[5] = NULL;
	MQSVGDraw_Value(m_Ptr, MQWIDGET_EDIT, (void*)ptr);
	
	return (result != 0);
}


//---------------------------------------------------------------------------
//  class MQCanvas
//---------------------------------------------------------------------------
MQCanvas::MQCanvas(void *ptr)
{
	m_Ptr = ptr;
	m_Owner = false;
}

MQCanvas::MQCanvas(int x1, int y1, int x2, int y2)
	: m_Ptr(nullptr)
{
	void *ptr[13];
	ptr[0] = (void*)"type";
	ptr[1] = (void*)"canvas";
	ptr[2] = (void*)"x1";
	ptr[3] = (void*)&x1;
	ptr[4] = (void*)"y1";
	ptr[5] = (void*)&y1;
	ptr[6] = (void*)"x2";
	ptr[7] = (void*)&x2;
	ptr[8] = (void*)"y2";
	ptr[9] = (void*)&y2;
	ptr[10] = (void*)"ptr";
	ptr[11] = (void*)&m_Ptr;
	ptr[12] = NULL;
	MQCanvas_Value(nullptr, MQWIDGET_CREATE, (void*)ptr);

	m_Owner = (m_Ptr != nullptr);
}

MQCanvas::~MQCanvas()
{
	if(m_Owner){
		void *ptr[1];
		ptr[0] = NULL;
		MQCanvas_Value(m_Ptr, MQWIDGET_DELETE, (void*)ptr);
	}
}

void MQCanvas::GetBitmap(unsigned char*& buffer, size_t& row_bytes)
{
	buffer = nullptr;
	row_bytes = 0;

	void *ptr[6];
	ptr[0] = (void*)"bitmap";
	ptr[1] = (void*)"buffer";
	ptr[2] = &buffer;
	ptr[3] = (void*)"row_bytes";
	ptr[4] = &row_bytes;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_GET, ptr);
}

void MQCanvas::GetCanvasRect(int& x, int& y, int& width, int& height)
{
	x = y = width = height = 0;

	void *ptr[10];
	ptr[0] = (void*)"rect";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"width";
	ptr[6] = &width;
	ptr[7] = (void*)"height";
	ptr[8] = &height;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_GET, ptr);
}

void MQCanvas::PushClipRect(int x, int y, int w, int h)
{
	void *ptr[10];
	ptr[0] = (void*)"pushcliprect";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::PopClipRect()
{
	void *ptr[2];
	ptr[0] = (void*)"popcliprect";
	ptr[1] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetColor(int r, int g, int b, int a)
{
	int values[4] = {r,g,b,a};
	void *ptr[4];
	ptr[0] = (void*)"color";
	ptr[1] = (void*)"rgba";
	ptr[2] = values;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetGradientColor(int x1, int y1, int x2, int y2, const std::vector<MQCanvasColor>& colors, const std::vector<float>& segments)
{
	assert(colors.size() == segments.size());
	int num = (int)colors.size();
	void *ptr[16];
	ptr[0] = (void*)"gradientcolorI";
	ptr[1] = (void*)"x1";
	ptr[2] = &x1;
	ptr[3] = (void*)"y1";
	ptr[4] = &y1;
	ptr[5] = (void*)"x2";
	ptr[6] = &x2;
	ptr[7] = (void*)"y2";
	ptr[8] = &y2;
	ptr[9] = (void*)"color_number";
	ptr[10] = &num;
	ptr[11] = (void*)"rgba";
	ptr[12] = (void*)&(*colors.begin());
	ptr[13] = (void*)"segment";
	ptr[14] = (void*)&(*segments.begin());
	ptr[15] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetGradientColor(float x1, float y1, float x2, float y2, const std::vector<MQCanvasColor>& colors, const std::vector<float>& segments)
{
	assert(colors.size() == segments.size());
	int num = (int)colors.size();
	void *ptr[16];
	ptr[0] = (void*)"gradientcolorF";
	ptr[1] = (void*)"x1";
	ptr[2] = &x1;
	ptr[3] = (void*)"y1";
	ptr[4] = &y1;
	ptr[5] = (void*)"x2";
	ptr[6] = &x2;
	ptr[7] = (void*)"y2";
	ptr[8] = &y2;
	ptr[9] = (void*)"color_number";
	ptr[10] = &num;
	ptr[11] = (void*)"rgba";
	ptr[12] = (void*)&(*colors.begin());
	ptr[13] = (void*)"segment";
	ptr[14] = (void*)&(*segments.begin());
	ptr[15] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetStrokeWidth(float width)
{
	void *ptr[4];
	ptr[0] = (void*)"strokewidth";
	ptr[1] = (void*)"width";
	ptr[2] = &width;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetStrokeCap(MQCANVAS_CAP_TYPE cap)
{
	void *ptr[4];
	ptr[0] = (void*)"strokecap";
	ptr[1] = (void*)"cap";
	switch(cap){
	case CAP_BUTT: ptr[2] = (void*)"butt"; break;
	case CAP_ROUND: ptr[2] = (void*)"round"; break;
	case CAP_SQUARE: ptr[2] = (void*)"square"; break;
	default: return;
	}
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetStrokeJoin(MQCANVAS_JOIN_TYPE join)
{
	void *ptr[4];
	ptr[0] = (void*)"strokejoin";
	ptr[1] = (void*)"join";
	switch(join){
	case JOIN_MITER: ptr[2] = (void*)"miter"; break;
	case JOIN_ROUND: ptr[2] = (void*)"round"; break;
	case JOIN_BEVEL: ptr[2] = (void*)"bevel"; break;
	default: return;
	}
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetStrokeMiterLimit(float limit)
{
	void *ptr[4];
	ptr[0] = (void*)"strokemiterlimit";
	ptr[1] = (void*)"limit";
	ptr[2] = &limit;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetStrokeDash(const std::vector<float>& intervals)
{
	int num = (int)intervals.size();
	void *ptr[6];
	ptr[0] = (void*)"strokedash";
	ptr[1] = (void*)"number";
	ptr[2] = &num;
	ptr[3] = (void*)"interval";
	ptr[4] = (void*)&(*intervals.begin());
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetFont(const wchar_t *fontname, bool bold)
{
	void *ptr[6];
	ptr[0] = (void*)"font";
	ptr[1] = (void*)"fontname";
	ptr[2] = (void*)fontname;
	ptr[3] = (void*)"bold";
	ptr[4] = &bold;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetFontSize(int size)
{
	void *ptr[4];
	ptr[0] = (void*)"fontsize";
	ptr[1] = (void*)"size";
	ptr[2] = &size;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetFontRateSize(float rate)
{
	void *ptr[4];
	ptr[0] = (void*)"fontratesize";
	ptr[1] = (void*)"rate";
	ptr[2] = &rate;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::SetAntiAlias(bool val)
{
	void *ptr[4];
	ptr[0] = (void*)"antialias";
	ptr[1] = (void*)"value";
	ptr[2] = &val;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_SET, ptr);
}

void MQCanvas::Clear(int r, int g, int b, int a)
{
	int values[4] = {r,g,b,a};
	void *ptr[4];
	ptr[0] = (void*)"clear";
	ptr[1] = (void*)"rgba";
	ptr[2] = values;
	ptr[3] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawLine(int x1, int y1, int x2, int y2)
{
	void *ptr[10];
	ptr[0] = (void*)"drawlineI";
	ptr[1] = (void*)"x1";
	ptr[2] = &x1;
	ptr[3] = (void*)"y1";
	ptr[4] = &y1;
	ptr[5] = (void*)"x2";
	ptr[6] = &x2;
	ptr[7] = (void*)"y2";
	ptr[8] = &y2;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawLine(float x1, float y1, float x2, float y2)
{
	void *ptr[10];
	ptr[0] = (void*)"drawlineF";
	ptr[1] = (void*)"x1";
	ptr[2] = &x1;
	ptr[3] = (void*)"y1";
	ptr[4] = &y1;
	ptr[5] = (void*)"x2";
	ptr[6] = &x2;
	ptr[7] = (void*)"y2";
	ptr[8] = &y2;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawPolyline(const POINT *points, int num_points)
{
	void *ptr[6];
	ptr[0] = (void*)"drawpolylineI";
	ptr[1] = (void*)"points";
	ptr[2] = (void*)points;
	ptr[3] = (void*)"num_points";
	ptr[4] = &num_points;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawPolyline(const MQCanvasPoint *points, int num_points)
{
	void *ptr[6];
	ptr[0] = (void*)"drawpolylineF";
	ptr[1] = (void*)"points";
	ptr[2] = (void*)points;
	ptr[3] = (void*)"num_points";
	ptr[4] = &num_points;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawCircle(int x, int y, float r)
{
	void *ptr[8];
	ptr[0] = (void*)"drawcircleI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"r";
	ptr[6] = &r;
	ptr[7] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawCircle(float x, float y, float r)
{
	void *ptr[8];
	ptr[0] = (void*)"drawcircleF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"r";
	ptr[6] = &r;
	ptr[7] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillCircle(int x, int y, float r)
{
	void *ptr[8];
	ptr[0] = (void*)"fillcircleI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"r";
	ptr[6] = &r;
	ptr[7] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillCircle(float x, float y, float r)
{
	void *ptr[8];
	ptr[0] = (void*)"fillcircleF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"r";
	ptr[6] = &r;
	ptr[7] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawEllipse(int x, int y, float rx, float ry)
{
	void *ptr[10];
	ptr[0] = (void*)"drawellipseI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"rx";
	ptr[6] = &rx;
	ptr[7] = (void*)"ry";
	ptr[8] = &ry;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawEllipse(float x, float y, float rx, float ry)
{
	void *ptr[10];
	ptr[0] = (void*)"drawellipseF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"rx";
	ptr[6] = &rx;
	ptr[7] = (void*)"ry";
	ptr[8] = &ry;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillEllipse(int x, int y, float rx, float ry)
{
	void *ptr[10];
	ptr[0] = (void*)"fillellipseI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"rx";
	ptr[6] = &rx;
	ptr[7] = (void*)"ry";
	ptr[8] = &ry;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillEllipse(float x, float y, float rx, float ry)
{
	void *ptr[10];
	ptr[0] = (void*)"fillellipseF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"rx";
	ptr[6] = &rx;
	ptr[7] = (void*)"ry";
	ptr[8] = &ry;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawRect(int x, int y, int w, int h)
{
	void *ptr[10];
	ptr[0] = (void*)"drawrectI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawRect(float x, float y, float w, float h)
{
	void *ptr[10];
	ptr[0] = (void*)"drawrectF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillRect(int x, int y, int w, int h)
{
	void *ptr[10];
	ptr[0] = (void*)"fillrectI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillRect(float x, float y, float w, float h)
{
	void *ptr[10];
	ptr[0] = (void*)"fillrectF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawRoundRect(int x, int y, int w, int h, int rx, int ry)
{
	void *ptr[14];
	ptr[0] = (void*)"drawroundrectI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = (void*)"rx";
	ptr[10] = &rx;
	ptr[11] = (void*)"ry";
	ptr[12] = &ry;
	ptr[13] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawRoundRect(float x, float y, float w, float h, float rx, float ry)
{
	void *ptr[14];
	ptr[0] = (void*)"drawroundrectF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = (void*)"rx";
	ptr[10] = &rx;
	ptr[11] = (void*)"ry";
	ptr[12] = &ry;
	ptr[13] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillRoundRect(int x, int y, int w, int h, int rx, int ry)
{
	void *ptr[14];
	ptr[0] = (void*)"fillroundrectI";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = (void*)"rx";
	ptr[10] = &rx;
	ptr[11] = (void*)"ry";
	ptr[12] = &ry;
	ptr[13] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillRoundRect(float x, float y, float w, float h, float rx, float ry)
{
	void *ptr[14];
	ptr[0] = (void*)"fillroundrectF";
	ptr[1] = (void*)"x";
	ptr[2] = &x;
	ptr[3] = (void*)"y";
	ptr[4] = &y;
	ptr[5] = (void*)"w";
	ptr[6] = &w;
	ptr[7] = (void*)"h";
	ptr[8] = &h;
	ptr[9] = (void*)"rx";
	ptr[10] = &rx;
	ptr[11] = (void*)"ry";
	ptr[12] = &ry;
	ptr[13] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawPolygon(const POINT *points, int num_points)
{
	void *ptr[6];
	ptr[0] = (void*)"drawpolygonI";
	ptr[1] = (void*)"points";
	ptr[2] = (void*)points;
	ptr[3] = (void*)"num_points";
	ptr[4] = &num_points;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawPolygon(const MQCanvasPoint *points, int num_points)
{
	void *ptr[6];
	ptr[0] = (void*)"drawpolygonF";
	ptr[1] = (void*)"points";
	ptr[2] = (void*)points;
	ptr[3] = (void*)"num_points";
	ptr[4] = &num_points;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillPolygon(const POINT *points, int num_points)
{
	void *ptr[6];
	ptr[0] = (void*)"fillpolygonI";
	ptr[1] = (void*)"points";
	ptr[2] = (void*)points;
	ptr[3] = (void*)"num_points";
	ptr[4] = &num_points;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::FillPolygon(const MQCanvasPoint *points, int num_points)
{
	void *ptr[6];
	ptr[0] = (void*)"fillpolygonF";
	ptr[1] = (void*)"points";
	ptr[2] = (void*)points;
	ptr[3] = (void*)"num_points";
	ptr[4] = &num_points;
	ptr[5] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawDIB(void *header, void *buffer, int x, int y)
{
	void *ptr[10];
	ptr[0] = (void*)"drawdib";
	ptr[1] = (void*)"header";
	ptr[2] = header;
	ptr[3] = (void*)"buffer";
	ptr[4] = buffer;
	ptr[5] = (void*)"x";
	ptr[6] = &x;
	ptr[7] = (void*)"y";
	ptr[8] = &y;
	ptr[9] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawDIB(void *header, void *buffer, int x, int y, int w, int h)
{
	void *ptr[14];
	ptr[0] = (void*)"drawdib";
	ptr[1] = (void*)"header";
	ptr[2] = header;
	ptr[3] = (void*)"buffer";
	ptr[4] = buffer;
	ptr[5] = (void*)"x";
	ptr[6] = &x;
	ptr[7] = (void*)"y";
	ptr[8] = &y;
	ptr[9] = (void*)"w";
	ptr[10] = &w;
	ptr[11] = (void*)"h";
	ptr[12] = &h;
	ptr[13] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawSVG(MQSVGDraw *svg, int x, int y, int w, int h)
{
	void *ptr[12];
	ptr[0] = (void*)"drawsvg";
	ptr[1] = (void*)"svg";
	ptr[2] = svg->m_Ptr;
	ptr[3] = (void*)"x";
	ptr[4] = &x;
	ptr[5] = (void*)"y";
	ptr[6] = &y;
	ptr[7] = (void*)"w";
	ptr[8] = &w;
	ptr[9] = (void*)"h";
	ptr[10] = &h;
	ptr[11] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

void MQCanvas::DrawText(const wchar_t *str, int x, int y, int w, int h, bool horz_center, bool vert_center)
{
	void *ptr[16];
	ptr[0] = (void*)"drawtext";
	ptr[1] = (void*)"string";
	ptr[2] = (void*)str;
	ptr[3] = (void*)"x";
	ptr[4] = &x;
	ptr[5] = (void*)"y";
	ptr[6] = &y;
	ptr[7] = (void*)"w";
	ptr[8] = &w;
	ptr[9] = (void*)"h";
	ptr[10] = &h;
	ptr[11] = (void*)"horz_center";
	ptr[12] = &horz_center;
	ptr[13] = (void*)"vert_center";
	ptr[14] = &vert_center;
	ptr[15] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);
}

POINT MQCanvas::MeasureText(const wchar_t *str)
{
	int x=0, y=0;
	void *ptr[8];
	ptr[0] = (void*)"measuretext";
	ptr[1] = (void*)"string";
	ptr[2] = (void*)str;
	ptr[3] = (void*)"x";
	ptr[4] = &x;
	ptr[5] = (void*)"y";
	ptr[6] = &y;
	ptr[7] = NULL;
	MQCanvas_Value(m_Ptr, MQWIDGET_EDIT, ptr);

	POINT p;
	p.x = x;
	p.y = y;
	return p;
}


//---------------------------------------------------------------------------
//  Global functions
//---------------------------------------------------------------------------

void *ExtractEventOption(void *option, const char *name)
{
	if (option != NULL){
		void **array = (void**)option;
		for (int i=0; array[i]!=NULL; i+=2){
			if (strcmp((char*)array[i], name) == 0)
				return array[i+1];
		}
	}
	return NULL;
}
/*
BOOL ExtractEventOptionBool(void *option, const char *name, BOOL defval)
{
	BOOL *ptr = (BOOL*)ExtractEventOption(option, name);
	return (ptr != NULL) ? *ptr : defval;
}
*/
int ExtractEventOptionInt(void *option, const char *name, int defval)
{
	int *ptr = (int*)ExtractEventOption(option, name);
	return (ptr != NULL) ? *ptr : defval;
}

float ExtractEventOptionFloat(void *option, const char *name, float defval)
{
	float *ptr = (float*)ExtractEventOption(option, name);
	return (ptr != NULL) ? *ptr : defval;
}

