#pragma once

#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "vectors.h"
#include "tools.h"
#include "Ini.h"
#include "structs.h"
#include "draw.h"
#include "functions.h"
#include "base.h"
#include "menu.h"
#include "aimbot.h"
#include "esp.h"
#include "hook.h"

extern bool unHookCg, unHookCa;

#define D3DX_PI 3.1415926535897932384626
#define D3DXToRadian(degree) ((degree) * (D3DX_PI / 180.0f))

static const char *Bones[] = {
	"j_helmet", "j_head", "j_neck",
	"j_shoulder_le", "j_elbow_le", "j_wrist_le", "j_elbow_le", "j_shoulder_le", "j_neck",
	"j_shoulder_ri", "j_elbow_ri", "j_wrist_ri", "j_elbow_ri", "j_shoulder_ri", "j_neck",
	"j_spineupper", "j_spinelower", "j_hip_le", "j_knee_le", "j_ankle_le", "j_knee_le",
	"j_hip_le", "j_spinelower", "j_hip_ri", "j_knee_ri", "j_ankle_ri"
};

static const char *boneNames[17] = {
	"j_head",
	"j_helmet",
	"j_neck",
	"j_shoulder_le",
	"j_shoulder_ri",
	"j_elbow_le",
	"j_elbow_ri",
	"j_wrist_le",
	"j_wrist_ri",
	"j_hip_ri",
	"j_hip_le",
	"j_mainroot",
	"j_knee_le",
	"j_knee_ri",
	"j_ankle_ri",
	"j_ankle_le",
	"j_ball_le",
};

enum
{
	ET_GENERAL,
	ET_PLAYER,
	ET_PLAYER_CORPSE,
	ET_ITEM,
	ET_MISSILE,
	ET_INVISIBLE,
	ET_SCRIPTMOVER,
	ET_SOUND_BLEND,
	ET_FX,
	ET_LOOP_FX,
	ET_PRIMARY_LIGHT,
	ET_TURRET,
	ET_HELICOPTER,
	ET_PLANE,
	ET_VEHICLE,
	ET_VEHICLE_CORPSE,
	ET_ACTOR,
	ET_ACTOR_SPAWNER,
	ET_ACTOR_CORPSE,
	ET_STREAMER_HINT,
	ET_ZBARRIER
};

enum
{
	j_head,
	j_helmet,
	j_neck,
	j_shoulder_le,
	j_shoulder_ri,
	j_elbow_le,
	j_elbow_ri,
	j_wrist_le,
	j_wrist_ri,
	j_hip_ri,
	j_hip_le,
	j_mainroot,
	j_knee_le,
	j_knee_ri,
	j_ankle_ri,
	j_ankle_le,
	j_ball_le,
};

enum
{
	AIMBOT_FOV,
	AIMBOT_SCREEN,
	AIMBOT_RAGE
};

enum
{
	AIMBOT_SILENT,
	AIMBOT_SNAP
};

static const char *aimbotType[] = { "Silent", "Snap" };
static const char *targetType[] = { "FOV", "On-Screen", "Rage" };

static float maroon[4] = { 0.5019608f, 0.0f, 0.0f, 1.0f };
static float dark_red[4] = { 0.5450981f, 0.0f, 0.0f, 1.0f };
static float brown[4] = { 0.6470588f, 0.1647059f, 0.1647059f, 1.0f };
static float firebrick[4] = { 0.6980392f, 0.1333333f, 0.1333333f, 1.0f };
static float crimson[4] = { 0.8627451f, 0.07843138f, 0.2352941f, 1.0f };
static float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float tomato[4] = { 1.0f, 0.3882353f, 0.2784314f, 1.0f };
static float coral[4] = { 1.0f, 0.4980392f, 0.3137255f, 1.0f };
static float indian_red[4] = { 0.8039216f, 0.3607843f, 0.3607843f, 1.0f };
static float light_coral[4] = { 0.9411765f, 0.5019608f, 0.5019608f, 1.0f };
static float dark_salmon[4] = { 0.9137255f, 0.5882353f, 0.4784314f, 1.0f };
static float salmon[4] = { 0.9803922f, 0.5019608f, 0.4470588f, 1.0f };
static float light_salmon[4] = { 1.0f, 0.627451f, 0.4784314f, 1.0f };
static float orange_red[4] = { 1.0f, 0.2705882f, 0.0f, 1.0f };
static float dark_orange[4] = { 1.0f, 0.5490196f, 0.0f, 1.0f };
static float orange[4] = { 1.0f, 0.6470588f, 0.0f, 1.0f };
static float gold[4] = { 1.0f, 0.8431373f, 0.0f, 1.0f };
static float dark_golden_rod[4] = { 0.7215686f, 0.5254902f, 0.04313726f, 1.0f };
static float golden_rod[4] = { 0.854902f, 0.6470588f, 0.1254902f, 1.0f };
static float pale_golden_rod[4] = { 0.9333333f, 0.9098039f, 0.6666667f, 1.0f };
static float dark_khaki[4] = { 0.7411765f, 0.7176471f, 0.4196078f, 1.0f };
static float khaki[4] = { 0.9411765f, 0.9019608f, 0.5490196f, 1.0f };
static float olive[4] = { 0.5019608f, 0.5019608f, 0.0f, 1.0f };
static float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
static float yellow_green[4] = { 0.6039216f, 0.8039216f, 0.1960784f, 1.0f };
static float dark_olive_green[4] = { 0.3333333f, 0.4196078f, 0.1843137f, 1.0f };
static float olive_drab[4] = { 0.4196078f, 0.5568628f, 0.1372549f, 1.0f };
static float lawn_green[4] = { 0.4862745f, 0.9882353f, 0.0f, 1.0f };
static float chart_reuse[4] = { 0.4980392f, 1.0f, 0.0f, 1.0f };
static float green_yellow[4] = { 0.6784314f, 1.0f, 0.1843137f, 1.0f };
static float dark_green[4] = { 0.0f, 0.3921569f, 0.0f, 1.0f };
static float green[4] = { 0.0f, 0.5019608f, 0.0f, 1.0f };
static float forest_green[4] = { 0.1333333f, 0.5450981f, 0.1333333f, 1.0f };
static float lime[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float lime_green[4] = { 0.1960784f, 0.8039216f, 0.1960784f, 1.0f };
static float light_green[4] = { 0.5647059f, 0.9333333f, 0.5647059f, 1.0f };
static float pale_green[4] = { 0.5960785f, 0.9843137f, 0.5960785f, 1.0f };
static float dark_sea_green[4] = { 0.5607843f, 0.7372549f, 0.5607843f, 1.0f };
static float medium_spring_green[4] = { 0.0f, 0.9803922f, 0.6039216f, 1.0f };
static float spring_green[4] = { 0.0f, 1.0f, 0.4980392f, 1.0f };
static float sea_green[4] = { 0.1803922f, 0.5450981f, 0.3411765f, 1.0f };
static float medium_aqua_marine[4] = { 0.4f, 0.8039216f, 0.6666667f, 1.0f };
static float medium_sea_green[4] = { 0.2352941f, 0.7019608f, 0.4431373f, 1.0f };
static float light_sea_green[4] = { 0.1254902f, 0.6980392f, 0.6666667f, 1.0f };
static float dark_slate_gray[4] = { 0.1843137f, 0.3098039f, 0.3098039f, 1.0f };
static float teal[4] = { 0.0f, 0.5019608f, 0.5019608f, 1.0f };
static float dark_cyan[4] = { 0.0f, 0.5450981f, 0.5450981f, 1.0f };
static float aqua[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
static float cyan[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
static float light_cyan[4] = { 0.8784314f, 1.0f, 1.0f, 1.0f };
static float dark_turquoise[4] = { 0.0f, 0.8078431f, 0.8196079f, 1.0f };
static float turquoise[4] = { 0.2509804f, 0.8784314f, 0.8156863f, 1.0f };
static float medium_turquoise[4] = { 0.282353f, 0.8196079f, 0.8f, 1.0f };
static float pale_turquoise[4] = { 0.6862745f, 0.9333333f, 0.9333333f, 1.0f };
static float aqua_marine[4] = { 0.4980392f, 1.0f, 0.8313726f, 1.0f };
static float powder_blue[4] = { 0.6901961f, 0.8784314f, 0.9019608f, 1.0f };
static float cadet_blue[4] = { 0.372549f, 0.6196079f, 0.627451f, 1.0f };
static float steel_blue[4] = { 0.2745098f, 0.509804f, 0.7058824f, 1.0f };
static float corn_flower_blue[4] = { 0.3921569f, 0.5843138f, 0.9294118f, 1.0f };
static float deep_sky_blue[4] = { 0.0f, 0.7490196f, 1.0f, 1.0f };
static float dodger_blue[4] = { 0.1176471f, 0.5647059f, 1.0f, 1.0f };
static float light_blue[4] = { 0.6784314f, 0.8470588f, 0.9019608f, 1.0f };
static float sky_blue[4] = { 0.5294118f, 0.8078431f, 0.9215686f, 1.0f };
static float light_sky_blue[4] = { 0.5294118f, 0.8078431f, 0.9803922f, 1.0f };
static float midnight_blue[4] = { 0.09803922f, 0.09803922f, 0.4392157f, 1.0f };
static float navy[4] = { 0.0f, 0.0f, 0.5019608f, 1.0f };
static float dark_blue[4] = { 0.0f, 0.0f, 0.5450981f, 1.0f };
static float medium_blue[4] = { 0.0f, 0.0f, 0.8039216f, 1.0f };
static float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
static float royal_blue[4] = { 0.254902f, 0.4117647f, 0.8823529f, 1.0f };
static float blue_violet[4] = { 0.5411765f, 0.1686275f, 0.8862745f, 1.0f };
static float indigo[4] = { 0.2941177f, 0.0f, 0.509804f, 1.0f };
static float dark_slate_blue[4] = { 0.282353f, 0.2392157f, 0.5450981f, 1.0f };
static float slate_blue[4] = { 0.4156863f, 0.3529412f, 0.8039216f, 1.0f };
static float medium_slate_blue[4] = { 0.4823529f, 0.4078431f, 0.9333333f, 1.0f };
static float medium_purple[4] = { 0.5764706f, 0.4392157f, 0.8588235f, 1.0f };
static float dark_magenta[4] = { 0.5450981f, 0.0f, 0.5450981f, 1.0f };
static float dark_violet[4] = { 0.5803922f, 0.0f, 0.827451f, 1.0f };
static float dark_orchid[4] = { 0.6f, 0.1960784f, 0.8f, 1.0f };
static float medium_orchid[4] = { 0.7294118f, 0.3333333f, 0.827451f, 1.0f };
static float purple[4] = { 0.5019608f, 0.0f, 0.5019608f, 1.0f };
static float thistle[4] = { 0.8470588f, 0.7490196f, 0.8470588f, 1.0f };
static float plum[4] = { 0.8666667f, 0.627451f, 0.8666667f, 1.0f };
static float violet[4] = { 0.9333333f, 0.509804f, 0.9333333f, 1.0f };
static float magenta[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
static float orchid[4] = { 0.854902f, 0.4392157f, 0.8392157f, 1.0f };
static float medium_violet_red[4] = { 0.7803922f, 0.08235294f, 0.5215687f, 1.0f };
static float pale_violet_red[4] = { 0.8588235f, 0.4392157f, 0.5764706f, 1.0f };
static float deep_pink[4] = { 1.0f, 0.07843138f, 0.5764706f, 1.0f };
static float hot_pink[4] = { 1.0f, 0.4117647f, 0.7058824f, 1.0f };
static float light_pink[4] = { 1.0f, 0.7137255f, 0.7568628f, 1.0f };
static float pink[4] = { 1.0f, 0.7529412f, 0.7960784f, 1.0f };
static float antique_white[4] = { 0.9803922f, 0.9215686f, 0.8431373f, 1.0f };
static float beige[4] = { 0.9607843f, 0.9607843f, 0.8627451f, 1.0f };
static float bisque[4] = { 1.0f, 0.8941177f, 0.7686275f, 1.0f };
static float blanched_almond[4] = { 1.0f, 0.9215686f, 0.8039216f, 1.0f };
static float wheat[4] = { 0.9607843f, 0.8705882f, 0.7019608f, 1.0f };
static float corn_silk[4] = { 1.0f, 0.972549f, 0.8627451f, 1.0f };
static float lemon_chiffon[4] = { 1.0f, 0.9803922f, 0.8039216f, 1.0f };
static float light_golden_rod_yellow[4] = { 0.9803922f, 0.9803922f, 0.8235294f, 1.0f };
static float light_yellow[4] = { 1.0f, 1.0f, 0.8784314f, 1.0f };
static float saddle_brown[4] = { 0.5450981f, 0.2705882f, 0.07450981f, 1.0f };
static float sienna[4] = { 0.627451f, 0.3215686f, 0.1764706f, 1.0f };
static float chocolate[4] = { 0.8235294f, 0.4117647f, 0.1176471f, 1.0f };
static float peru[4] = { 0.8039216f, 0.5215687f, 0.2470588f, 1.0f };
static float sandy_brown[4] = { 0.9568627f, 0.6431373f, 0.3764706f, 1.0f };
static float burly_wood[4] = { 0.8705882f, 0.7215686f, 0.5294118f, 1.0f };
static float tancol[4] = { 0.8235294f, 0.7058824f, 0.5490196f, 1.0f };
static float rosy_brown[4] = { 0.7372549f, 0.5607843f, 0.5607843f, 1.0f };
static float moccasin[4] = { 1.0f, 0.8941177f, 0.7098039f, 1.0f };
static float navajo_white[4] = { 1.0f, 0.8705882f, 0.6784314f, 1.0f };
static float peach_puff[4] = { 1.0f, 0.854902f, 0.7254902f, 1.0f };
static float misty_rose[4] = { 1.0f, 0.8941177f, 0.8823529f, 1.0f };
static float lavender_blush[4] = { 1.0f, 0.9411765f, 0.9607843f, 1.0f };
static float linen[4] = { 0.9803922f, 0.9411765f, 0.9019608f, 1.0f };
static float old_lace[4] = { 0.9921569f, 0.9607843f, 0.9019608f, 1.0f };
static float papaya_whip[4] = { 1.0f, 0.9372549f, 0.8352941f, 1.0f };
static float sea_shell[4] = { 1.0f, 0.9607843f, 0.9333333f, 1.0f };
static float mint_cream[4] = { 0.9607843f, 1.0f, 0.9803922f, 1.0f };
static float slate_gray[4] = { 0.4392157f, 0.5019608f, 0.5647059f, 1.0f };
static float light_slate_gray[4] = { 0.4666667f, 0.5333334f, 0.6f, 1.0f };
static float light_steel_blue[4] = { 0.6901961f, 0.7686275f, 0.8705882f, 1.0f };
static float lavender[4] = { 0.9019608f, 0.9019608f, 0.9803922f, 1.0f };
static float floral_white[4] = { 1.0f, 0.9803922f, 0.9411765f, 1.0f };
static float alice_blue[4] = { 0.9411765f, 0.972549f, 1.0f, 1.0f };
static float ghost_white[4] = { 0.972549f, 0.972549f, 1.0f, 1.0f };
static float honeydew[4] = { 0.9411765f, 1.0f, 0.9411765f, 1.0f };
static float ivory[4] = { 1.0f, 1.0f, 0.9411765f, 1.0f };
static float azure[4] = { 0.9411765f, 1.0f, 1.0f, 1.0f };
static float snow[4] = { 1.0f, 0.9803922f, 0.9803922f, 1.0f };
static float dim_gray[4] = { 0.4117647f, 0.4117647f, 0.4117647f, 1.0f };
static float gray[4] = { 0.5019608f, 0.5019608f, 0.5019608f, 1.0f };
static float dark_gray[4] = { 0.6627451f, 0.6627451f, 0.6627451f, 1.0f };
static float silver[4] = { 0.7529412f, 0.7529412f, 0.7529412f, 1.0f };
static float light_gray[4] = { 0.827451f, 0.827451f, 0.827451f, 1.0f };
static float gainsboro[4] = { 0.8627451f, 0.8627451f, 0.8627451f, 1.0f };
static float white_smoke[4] = { 0.9607843f, 0.9607843f, 0.9607843f, 1.0f };
static float Black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static float lightBlack[4] = { 0.0f, 0.0f, 0.0f, 0.3921569f };
static float White[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float Red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float Lime[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float Blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
static float Yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
static float Cyan[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
static float Magenta[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
static float Silver[4] = { 0.7529412f, 0.7529412f, 0.7529412f, 1.0f };
static float Gray[4] = { 0.5019608f, 0.5019608f, 0.5019608f, 1.0f };
static float Maroon[4] = { 0.5019608f, 0.0f, 0.0f, 1.0f };
static float Olive[4] = { 0.5019608f, 0.5019608f, 0.0f, 1.0f };
static float Green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float Purple[4] = { 0.5019608f, 0.0f, 0.5019608f, 1.0f };
static float Teal[4] = { 0.0f, 0.5019608f, 0.5019608f, 1.0f };
static float Navy[4] = { 0.0f, 0.0f, 0.5019608f, 1.0f };
static float darkMenuColor[4] = { 0.0627451f, 0.0627451f, 0.0627451f, 1.0f };
static float lightMenuColor[4] = { 0.1058824f, 0.1058824f, 0.1058824f, 1.0f };
static float xButtonColor[4] = { 0.5568628f, 0.09411765f, 0.09411765f, 1.0f };
static float mint[4] = { 0.0f, 1.0f, 0.7333333f, 1.0f };
