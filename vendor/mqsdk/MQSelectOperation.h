//---------------------------------------------------------------------------
//
//   MQSelectOperation.h      Copyright(C) 1999-2023, tetraface Inc.
//
//		A selection with a rectangle or a rope
//
//    　範囲・投げ縄選択
//
//---------------------------------------------------------------------------

#ifndef _MQSELECTOPERATION_H_
#define _MQSELECTOPERATION_H_

#include "MQBasePlugin.h"

class MQSelectOperation {
public:
	enum SELECT_TYPE {
		SELECT_NONE,
		SELECT_RECT,
		SELECT_ROPE,
	};

	MQSelectOperation();

	void Clear();

	void Begin(SELECT_TYPE type, POINT mousePos);
	void Move(POINT mousePos);
	bool IsValid() const;
	bool IsInside(POINT p) const { return IsInside(MQPoint((float)p.x, (float)p.y, 0.0f)); }
	bool IsInside(const MQPoint& p) const;
	void Finish();

	void Draw(MQCommandPlugin *plugin, MQDocument doc, MQScene scene);

	SELECT_TYPE GetType() const { return Type; }

private:
	SELECT_TYPE Type;
	POINT PrevPos, DownPos;
	std::vector<POINT> RopePoints;
};


#endif //_MQSELECTOPERATION_H_
