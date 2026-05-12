//---------------------------------------------------------------------------
//
//   MQSelectOperation.cpp      Copyright(C) 1999-2023, tetraface Inc.
//
//		A selection with a rectangle or a rope
//
//    　範囲・投げ縄選択
//
//---------------------------------------------------------------------------

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif
#include <algorithm>
#include "MQSelectOperation.h"
#include "MQ3DLib.h"


MQSelectOperation::MQSelectOperation()
{
	Type = SELECT_NONE;
}

void MQSelectOperation::Clear()
{
	Type = SELECT_NONE;
	RopePoints.clear();
}

void MQSelectOperation::Begin(SELECT_TYPE type, POINT mousePos)
{
	Type = type;
	DownPos = mousePos;
	PrevPos = mousePos;
	RopePoints.clear();

	switch(Type){
	case SELECT_RECT:
		break;
	case SELECT_ROPE:
		RopePoints.push_back(mousePos);
		break;
	}
}

void MQSelectOperation::Move(POINT mousePos)
{
	PrevPos = mousePos;

	switch(Type){
	case SELECT_RECT:
		break;
	case SELECT_ROPE:
		if(!RopePoints.empty()){
			if(RopePoints.back().x != mousePos.x || RopePoints.back().y != mousePos.y){
				RopePoints.push_back(mousePos);
			}
		}
		break;
	}
}

bool MQSelectOperation::IsValid() const
{
	switch(Type){
	case SELECT_RECT:
		if(PrevPos.x != DownPos.x || PrevPos.y != DownPos.y){
			return true;
		}
		break;
	case SELECT_ROPE:
		if(RopePoints.size() >= 3){
			return true;
		}
		break;
	}
	return false;
}

bool MQSelectOperation::IsInside(const MQPoint& pos) const
{
	switch(Type){
	case SELECT_RECT:
		{
			float x1 = (float)std::min(PrevPos.x, DownPos.x);
			float x2 = (float)std::max(PrevPos.x, DownPos.x);
			float y1 = (float)std::min(PrevPos.y, DownPos.y);
			float y2 = (float)std::max(PrevPos.y, DownPos.y);
			if(x1 <= pos.x && pos.x <= x2 && y1 <= pos.y && pos.y <= y2){
				return true;
			}
		}
		break;
	case SELECT_ROPE:
		if(RopePoints.size() >= 3)
		{
			int count = 0;
			for(size_t j=0; j<RopePoints.size(); j++)
			{
				size_t j1 = (j+1) % RopePoints.size();
				size_t j2 = (j+2) % RopePoints.size();
				if((pos.y > RopePoints[j].y && pos.y < RopePoints[j1].y)
				|| (pos.y < RopePoints[j].y && pos.y > RopePoints[j1].y))
				{
					float t = (pos.y - RopePoints[j].y) / (RopePoints[j1].y - RopePoints[j].y);
					if(pos.x < RopePoints[j].x*(1-t) + RopePoints[j1].x*t)
						count++;
				}
				else if(pos.x < RopePoints[j1].x && pos.y == RopePoints[j1].y)
				{
					if((pos.y > RopePoints[j].y && pos.y < RopePoints[j2].y)
					|| (pos.y < RopePoints[j].y && pos.y > RopePoints[j2].y))
						count++;
				}
			}

			return (count & 1);
		}
		break;
	}
	return false;
}

void MQSelectOperation::Finish()
{
	Clear();
}

void MQSelectOperation::Draw(MQCommandPlugin *plugin, MQDocument doc, MQScene scene)
{
	switch(Type){
	case SELECT_RECT:
		{
			MQObject draw = plugin->CreateDrawingObject(doc, MQCommandPlugin::DRAW_OBJECT_LINE);
			draw->AddRenderFlag(MQOBJECT_RENDER_OVERWRITELINE);

			int vi1 = draw->AddVertex(scene->ConvertScreenTo3D(MQPoint((float)DownPos.x, (float)DownPos.y, scene->GetFrontZ())));
			int vi2 = draw->AddVertex(scene->ConvertScreenTo3D(MQPoint((float)PrevPos.x, (float)DownPos.y, scene->GetFrontZ())));
			int vi3 = draw->AddVertex(scene->ConvertScreenTo3D(MQPoint((float)PrevPos.x, (float)PrevPos.y, scene->GetFrontZ())));
			int vi4 = draw->AddVertex(scene->ConvertScreenTo3D(MQPoint((float)DownPos.x, (float)PrevPos.y, scene->GetFrontZ())));

			int nvi[2];
			nvi[0] = vi1;
			nvi[1] = vi2;
			draw->AddFace(2, nvi);
			nvi[0] = vi2;
			nvi[1] = vi3;
			draw->AddFace(2, nvi);
			nvi[0] = vi3;
			nvi[1] = vi4;
			draw->AddFace(2, nvi);
			nvi[0] = vi4;
			nvi[1] = vi1;
			draw->AddFace(2, nvi);
		}
		break;
	case SELECT_ROPE:
		if(RopePoints.size() >= 2)
		{
			MQObject draw = plugin->CreateDrawingObject(doc, MQCommandPlugin::DRAW_OBJECT_LINE);
			draw->AddRenderFlag(MQOBJECT_RENDER_OVERWRITELINE);

			for(size_t i=0; i<RopePoints.size(); i++){
				MQPoint p = scene->ConvertScreenTo3D(MQPoint((float)RopePoints[i].x, (float)RopePoints[i].y, scene->GetFrontZ()));
				draw->AddVertex(p);
			}

			for(size_t i=0; i<RopePoints.size(); i++){
				int nvi[2];
				nvi[0] = (int)i;
				nvi[1] = (int)((i+1) % RopePoints.size());
				draw->AddFace(2, nvi);
			}
		}
		break;
	}
}

