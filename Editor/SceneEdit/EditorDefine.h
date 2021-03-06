/********************************************************************
	created:	20:12:2012   1:02
	filename: 	F:\MiniCraft\Editor\SceneEdit\EditorDefine.h
	author:		maval
	
	purpose:	常量定义
*********************************************************************/

#ifndef EditorDefine_h__
#define EditorDefine_h__


const	int		EDITOR_CLIENT_W			=	1024;
const	int		EDITOR_CLIENT_H			=	768;
const	int		FPS					=	100;
const	float	TIME_PER_FRAME		=	1.0f / FPS;
const	int		MESH_ICON_SIZE		=	64;
const	int		RES_SELECTOR_COLUMN_WIDTH	=	80;
const	String	MAIN_CAMERA_NAME	=	"MainCamera";
const	int		TERRAIN_MAX_LAYER	=	5;	//最多5层地形纹理混合

//场景查询掩码
enum eQueryMask
{
	eQueryMask_Default	=	0,
	eQueryMask_Entity = 1 << 0
};

enum eAxis
{
	eAxis_X,
	eAxis_Y,
	eAxis_Z,
	eAxis_None
};

//摄像机类型
enum eCameraType
{
	eCameraType_RTS,
	eCameraType_ModelViewer
};


#endif // EditorDefine_h__