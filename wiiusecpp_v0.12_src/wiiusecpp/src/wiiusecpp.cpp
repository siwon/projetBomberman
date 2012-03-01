/*
 *wiiusecpp.cpp
 *
 *Written By:
 *James Thomas
 *Email: jt@missioncognition.org
 *
 *Copyright 2009
 *
 *This file is part of wiiusecpp.
 *
 *This program is free software; you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation; either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * Note:  This C++ library is a (very) thin wrapper of the the wiiuse library.
 *        See http://www.wiiuse.net to get the wiiuse library which is required
 *        to build this package.  A SWIG based Python wrapper for this C++ library
 *        is available from http://www.missioncognition.org.
 */

#include <iostream>

#include <wiiuse.h>
#include "wiiusecpp.h"

using namespace std;

/*
 * CButtonBase class methods.
 */
CButtonBase::CButtonBase(void *ButtonsPtr, void *ButtonsHeldPtr, void *ButtonsReleasedPtr)
{
    mpBtnsPtr = ButtonsPtr;
    mpBtnsHeldPtr = ButtonsHeldPtr;
    mpBtnsReleasedPtr = ButtonsReleasedPtr;
}

int CButtonBase::isPressed(int Button)
{
    return (Cast(mpBtnsPtr) & Button) == Button;
}

int CButtonBase::isHeld(int Button)
{
    return (Cast(mpBtnsHeldPtr) & Button) == Button;
}

int CButtonBase::isReleased(int Button)
{
    return (Cast(mpBtnsReleasedPtr) & Button) == Button;
}

int CButtonBase::isJustPressed(int Button)
{
    return ((Cast(mpBtnsPtr) & Button) == Button) && ((Cast(mpBtnsHeldPtr) & Button) != Button);
}

/*
 * Initializers for classes derrived from CButtonBase.
 */
CButtons::CButtons(void *ButtonsPtr, void *ButtonsHeldPtr, void *ButtonsReleasedPtr) :
    CButtonBase(ButtonsPtr, ButtonsHeldPtr, ButtonsReleasedPtr)
{
}

CNunchukButtons::CNunchukButtons(void *ButtonsPtr, void *ButtonsHeldPtr, void *ButtonsReleasedPtr) :
    CButtonBase(ButtonsPtr, ButtonsHeldPtr, ButtonsReleasedPtr)
{
}

CClassicButtons::CClassicButtons(void *ButtonsPtr, void *ButtonsHeldPtr, void *ButtonsReleasedPtr) :
    CButtonBase(ButtonsPtr, ButtonsHeldPtr, ButtonsReleasedPtr)
{
}

CGH3Buttons::CGH3Buttons(void *ButtonsPtr, void *ButtonsHeldPtr, void *ButtonsReleasedPtr) :
    CButtonBase(ButtonsPtr, ButtonsHeldPtr, ButtonsReleasedPtr)
{
}

/*
 * CJoystick class methods.
 */

CJoystick::CJoystick(struct joystick_t *JSPtr)
{
    mpJoystickPtr = JSPtr;
}

void CJoystick::GetMaxCal(int &X, int &Y)
{
    X = mpJoystickPtr->max.x;
    Y = mpJoystickPtr->max.y;
}

void CJoystick::SetMaxCal(int X, int Y)
{
    mpJoystickPtr->max.x = X;
    mpJoystickPtr->max.y = Y;
}

void CJoystick::GetMinCal(int &X, int &Y)
{
    X = mpJoystickPtr->min.x;
    Y = mpJoystickPtr->min.y;
}

void CJoystick::SetMinCal(int X, int Y)
{
    mpJoystickPtr->min.x = X;
    mpJoystickPtr->min.y = Y;
}

void CJoystick::GetCenterCal(int &X, int &Y)
{
    X = mpJoystickPtr->center.x;
    Y = mpJoystickPtr->center.y;
}

void CJoystick::SetCenterCal(int X, int Y)
{
    mpJoystickPtr->center.x = X;
    mpJoystickPtr->center.y = Y;
}

void CJoystick::GetPosition(float &Angle, float &Magnitude)
{
    Angle = mpJoystickPtr->ang;
    Magnitude = mpJoystickPtr->mag;
}

/*
 * CAccelerometer class methods.
 */

CAccelerometer::CAccelerometer(struct accel_t *AccelCalPtr, struct vec3b_t *AccelerationPtr, int *AccelThresholdPtr,
                               struct orient_t *OrientationPtr, float *OrientationThresholdPtr,
                               struct gforce_t *GForcePtr)
{
    mpAccelCalibPtr = AccelCalPtr;
    mpAccelPtr = AccelerationPtr;
    mpOrientPtr = OrientationPtr;
    mpGForcePtr = GForcePtr;
    mpAccelThresholdPtr = AccelThresholdPtr;
    mpOrientThresholdPtr = OrientationThresholdPtr;
}

float CAccelerometer::SetSmoothAlpha(float Alpha)
{
    float old_value;

    old_value = mpAccelCalibPtr->st_alpha;

    mpAccelCalibPtr->st_alpha = Alpha;

    return old_value;
}

float CAccelerometer::GetOrientThreshold()
{
    return *mpOrientThresholdPtr;
}

void CAccelerometer::SetOrientThreshold(float Threshold)
{
    *mpOrientThresholdPtr = Threshold;
}

int CAccelerometer::GetAccelThreshold()
{
    return *mpAccelThresholdPtr;
}

void CAccelerometer::SetAccelThreshold(int Threshold)
{
    *mpAccelThresholdPtr = Threshold;
}

void CAccelerometer::GetOrientation(float &Pitch, float &Roll, float &Yaw)
{
    Pitch = mpOrientPtr->pitch;
    Roll = mpOrientPtr->roll;
    Yaw = mpOrientPtr->yaw;
}
void CAccelerometer::GetRawOrientation(float &Pitch, float &Roll)
{
    Pitch = mpOrientPtr->a_pitch;
    Roll = mpOrientPtr->a_roll;
}

void CAccelerometer::GetGravityCalVector(float &X, float &Y, float &Z)
{
    X = mpAccelCalibPtr->cal_g.x;
    Y = mpAccelCalibPtr->cal_g.y;
    Z = mpAccelCalibPtr->cal_g.z;
}

void CAccelerometer::SetGravityCalVector(float X, float Y, float Z)
{
    mpAccelCalibPtr->cal_g.x = X;
    mpAccelCalibPtr->cal_g.y = Y;
    mpAccelCalibPtr->cal_g.z = Z;
}

void CAccelerometer::GetGravityVector(float &X, float &Y, float &Z)
{
    X = mpGForcePtr->x;
    Y = mpGForcePtr->y;
    Z = mpGForcePtr->z;
}

/*
 * CIRDot class methods.
 */

CIRDot::CIRDot()
{
    mpDotPtr = NULL;
}

CIRDot::CIRDot(struct ir_dot_t *DotPtr)
{
    mpDotPtr = DotPtr;
}

CIRDot::CIRDot(const CIRDot &copyin) // Copy constructor to handle pass by value.
{
    mpDotPtr = copyin.mpDotPtr;
}

int CIRDot::isVisible()
{
    return mpDotPtr->visible;
}

int CIRDot::GetSize()
{
    return mpDotPtr->size;
}

int CIRDot::GetOrder()
{
    return mpDotPtr->order;
}

void CIRDot::GetCoordinate(int &X, int &Y)
{
    X = mpDotPtr->x;
    Y = mpDotPtr->y;
}

void CIRDot::GetRawCoordinate(int &X, int &Y)
{
    X = mpDotPtr->rx;
    Y = mpDotPtr->ry;
}

/*
 * CIR class methods.
 */

CIR::CIR(struct wiimote_t *wmPtr)
{
    mpWiimotePtr = wmPtr;
}

void CIR::SetMode(CIR::OnOffSelection State)
{
    wiiuse_set_ir(mpWiimotePtr, State);
}

void CIR::SetVres(unsigned int x, unsigned int y)
{
    wiiuse_set_ir_vres(mpWiimotePtr, x, y);
}

CIR::BarPositions CIR::GetBarPositionSetting()
{
    return (CIR::BarPositions) mpWiimotePtr->ir.pos;
}

void CIR::SetBarPosition(CIR::BarPositions PositionSelection)
{
    wiiuse_set_ir_position(mpWiimotePtr, (ir_position_t) PositionSelection);
}

CIR::AspectRatioSelections CIR::GetAspectRatioSetting()
{
    return (CIR::AspectRatioSelections) mpWiimotePtr->ir.aspect;
}

void CIR::SetAspectRatio(CIR::AspectRatioSelections AspectRatioSelection)
{
    wiiuse_set_aspect_ratio(mpWiimotePtr, (enum aspect_t) AspectRatioSelection);
}

void CIR::SetSensitivity(int Level)
{
    wiiuse_set_ir_sensitivity(mpWiimotePtr, Level);
}

int CIR::GetSensitivity()
{
    int level = 0;

    if(mpWiimotePtr->state & 0x0200)
        level = 1;
    else if(mpWiimotePtr->state & 0x0400)
        level = 2;
    else if(mpWiimotePtr->state & 0x0800)
        level = 3;
    else if(mpWiimotePtr->state & 0x1000)
        level = 4;
    else if(mpWiimotePtr->state & 0x2000)
        level = 5;

    return level;
}

int CIR::GetNumDots()
{
    return mpWiimotePtr->ir.num_dots;
}

std::vector<CIRDot>& CIR::GetDots()
{
    int index;

    // Empty the array of irdots before reloading
    mpIRDotsVector.clear();

    for(index = 0; index < mpWiimotePtr->ir.num_dots; index++)
    {
        CIRDot dot((struct ir_dot_t *) (&(mpWiimotePtr->ir.dot[index])));
        mpIRDotsVector.push_back(dot);
    }

    //return numConnected;
    return mpIRDotsVector;
}

void CIR::GetOffset(int &X, int &Y)
{
    X = mpWiimotePtr->ir.offset[0];
    Y = mpWiimotePtr->ir.offset[1];
}

int CIR::GetState()
{
    return mpWiimotePtr->ir.state;
}

void CIR::GetCursorPositionAbsolute(int &X, int &Y)
{
    X = mpWiimotePtr->ir.ax;
    Y = mpWiimotePtr->ir.ay;
}

void CIR::GetCursorPosition(int &X, int &Y)
{
    X = mpWiimotePtr->ir.x;
    Y = mpWiimotePtr->ir.y;
}

float CIR::GetPixelDistance()
{
    return mpWiimotePtr->ir.distance;
}

float CIR::GetDistance()
{
    return mpWiimotePtr->ir.z;
}

/*
 * CExpansionDevice class methods.  This is a container class so there is not much.
 */

CExpansionDevice::CExpansionDevice(struct expansion_t *ExpPtr) :
    Nunchuk(ExpPtr), Classic(ExpPtr), GuitarHero3(ExpPtr)
{
    mpExpansionPtr = ExpPtr;
}

CExpansionDevice::ExpTypes CExpansionDevice::GetType()
{
    return (CExpansionDevice::ExpTypes) (mpExpansionPtr->type);
}

/*
 * CNunchuk class methods.
 */

CNunchuk::CNunchuk(struct expansion_t *ExpPtr):
    Buttons((void *) &(ExpPtr->nunchuk.btns), (void *) &(ExpPtr->nunchuk.btns_held),
            (void *) &(ExpPtr->nunchuk.btns_released)), Joystick(&(ExpPtr->nunchuk.js)),
            Accelerometer(&(ExpPtr->nunchuk.accel_calib), &(ExpPtr->nunchuk.accel), &(ExpPtr->nunchuk.accel_threshold),
                          &(ExpPtr->nunchuk.orient), &(ExpPtr->nunchuk.orient_threshold), &(ExpPtr->nunchuk.gforce))
{
}

/*
 * CClassic class methods.
 */

CClassic::CClassic(struct expansion_t *ExpPtr):
    Buttons((void *) &(mpClassicPtr->btns), (void *) &(mpClassicPtr->btns_held), (void *) &(mpClassicPtr->btns_released)),
            LeftJoystick(&(mpClassicPtr->ljs)), RightJoystick(&(mpClassicPtr->rjs))
{
    // Initialize the expansion pointer.
    mpClassicPtr = &(ExpPtr->classic);
}

float CClassic::GetLShoulderButton()
{
    return mpClassicPtr->l_shoulder;
}

float CClassic::GetRShoulderButton()
{
    return mpClassicPtr->r_shoulder;
}

/*
 * CGuitarHero3 class methods.
 */

CGuitarHero3::CGuitarHero3(struct expansion_t *ExpPtr):
    Buttons((void *) &(mpGH3Ptr->btns), (void *) &(mpGH3Ptr->btns_held), (void *) &(mpGH3Ptr->btns_released)),
            Joystick(&(mpGH3Ptr->js))
{
    // Initialize the expansion pointer.
    mpGH3Ptr = &(ExpPtr->gh3);
}

float CGuitarHero3::GetWhammyBar()
{
    return mpGH3Ptr->whammy_bar;
}

/*
 * CWiimote class methods.
 */

CWiimote::CWiimote() : // SWIG insisted it exist for the vectors. Hopefully it will only be used for copy.
    IR(NULL), Buttons(NULL, NULL, NULL), Accelerometer((accel_t*) NULL, (vec3b_t*) NULL, (int*) &(mpTempInt),
                                                       (orient_t*) NULL, (float*) &(mpTempFloat), (gforce_t*) NULL),
            ExpansionDevice(NULL)
{
    mpWiimotePtr = NULL;
}

CWiimote::CWiimote(struct wiimote_t *wmPtr):
    IR(wmPtr), Buttons((void *) &(wmPtr->btns), (void *) &(wmPtr->btns_held), (void *) &(wmPtr->btns_released)),
            Accelerometer((accel_t*) &(wmPtr->accel_calib), (vec3b_t*) &(wmPtr->accel),
                          (int*) &(wmPtr->accel_threshold), (orient_t*) &(wmPtr->orient),
                          (float*) &(wmPtr->orient_threshold), (gforce_t*) &(wmPtr->gforce)),
            ExpansionDevice((struct expansion_t*) &(wmPtr->exp))
{
    mpWiimotePtr = wmPtr;
}

CWiimote::CWiimote(const CWiimote &copyin) : // Copy constructor to handle pass by value.
            IR(copyin.mpWiimotePtr),
            Buttons((void *) &(copyin.mpWiimotePtr->btns), (void *) &(copyin.mpWiimotePtr->btns_held),
                    (void *) &(copyin.mpWiimotePtr->btns_released)),
            Accelerometer((accel_t*) &(copyin.mpWiimotePtr->accel_calib), (vec3b_t*) &(copyin.mpWiimotePtr->accel),
                          (int*) &(copyin.mpWiimotePtr->accel_threshold), (orient_t*) &(copyin.mpWiimotePtr->orient),
                          (float*) &(copyin.mpWiimotePtr->orient_threshold), (gforce_t*) &(copyin.mpWiimotePtr->gforce)),
            ExpansionDevice((struct expansion_t*) &(copyin.mpWiimotePtr->exp))
{
    mpWiimotePtr = copyin.mpWiimotePtr;
}

void CWiimote::Disconnected()
{
    wiiuse_disconnected(mpWiimotePtr);
}

void CWiimote::SetRumbleMode(CWiimote::OnOffSelection State)
{
    wiiuse_rumble(mpWiimotePtr, State);
}

void CWiimote::ToggleRumble()
{
    wiiuse_toggle_rumble(mpWiimotePtr);
}

int CWiimote::GetLEDs()
{
    return mpWiimotePtr->leds;
}

void CWiimote::SetLEDs(int LEDs)
{
    wiiuse_set_leds(mpWiimotePtr, LEDs);
}

float CWiimote::GetBatteryLevel()
{
    return mpWiimotePtr->battery_level;
}

int CWiimote::GetHandshakeState()
{
    return mpWiimotePtr->handshake_state;
}

CWiimote::EventTypes CWiimote::GetEvent()
{
    return (CWiimote::EventTypes) mpWiimotePtr->event;
}

const unsigned char *CWiimote::GetEventBuffer()
{
    return mpWiimotePtr->event_buf;
}

void CWiimote::SetMotionSensingMode(CWiimote::OnOffSelection State)
{
    wiiuse_motion_sensing(mpWiimotePtr, State);
}

void CWiimote::ReadData(unsigned char *Buffer, unsigned int Offset, unsigned int Length)
{
    wiiuse_read_data(mpWiimotePtr, Buffer, Offset, Length);
}

void CWiimote::WriteData(unsigned int Address, unsigned char *Data, unsigned int Length)
{
    wiiuse_write_data(mpWiimotePtr, Address, Data, Length);
}

void CWiimote::UpdateStatus()
{
    wiiuse_status(mpWiimotePtr);
}

int CWiimote::GetID()
{
    return mpWiimotePtr->unid;
}

int CWiimote::GetState()
{
    return mpWiimotePtr->state;
}

int CWiimote::GetFlags()
{
    return mpWiimotePtr->flags;
}

int CWiimote::SetFlags(int Enable, int Disable)
{
    return wiiuse_set_flags(mpWiimotePtr, Enable, Disable);
}

void CWiimote::Resync()
{
    wiiuse_resync(mpWiimotePtr);
}

void CWiimote::Disconnect()
{
    wiiuse_disconnect(mpWiimotePtr);
}

int CWiimote::isUsingACC()
{
    return (mpWiimotePtr->state & 0x0020) != 0;
}

int CWiimote::isUsingEXP()
{
    return (mpWiimotePtr->state & 0x0040) != 0;
}

int CWiimote::isUsingIR()
{
    return (mpWiimotePtr->state & 0x0080) != 0;
}

int CWiimote::isUsingSpeaker()
{
    return (mpWiimotePtr->state & 0x0100) != 0;
}

int CWiimote::isLEDSet(int LEDNum)
{
    int result = 0;

    switch(LEDNum)
    {
        case 1:
            result = (mpWiimotePtr->leds & LED_1) != 0;
            break;
        case 2:
            result = (mpWiimotePtr->leds & LED_2) != 0;
            break;
        case 3:
            result = (mpWiimotePtr->leds & LED_3) != 0;
            break;
        case 4:
            result = (mpWiimotePtr->leds & LED_4) != 0;
        default:
            result = 0;
    }

    return result;
}

/*
 * Wii Class Methods
 */

CWii::CWii()
{
    mpWiimoteArraySize = 4;
    mpWiimoteArray = wiiuse_init(mpWiimoteArraySize);
    cout << "wiiusecpp / pywii by Jim Thomas (jt@missioncognition.net)" << endl;
    cout << "Download from http://missioncognition.net/" << endl;
}

CWii::CWii(int MaxNumWiimotes)
{
    mpWiimoteArraySize = MaxNumWiimotes;
    mpWiimoteArray = wiiuse_init(mpWiimoteArraySize);
    cout << "wiiusecpp / pywii by Jim Thomas (jt@missioncognition.net)" << endl;
    cout << "Download from http://missioncognition.net/" << endl;
}

CWii::~CWii()
{
    wiiuse_cleanup((struct wiimote_t**) mpWiimoteArray, mpWiimoteArraySize);
}

void CWii::RefreshWiimotes()
{
    int index;

    // This approach is a bit wasteful but it will work.  The other
    // option is to force the user to handle disconnect events to remove
    // wiimotes from the array.
    mpWiimotesVector.clear();

    for(index = 0; index < mpWiimoteArraySize; index++)
    {
        if((mpWiimoteArray[index]->state & 0x0008) != 0)
        {
            CWiimote wm(mpWiimoteArray[index]);
            mpWiimotesVector.push_back(wm);
        }
    }
}

int CWii::GetNumConnectedWiimotes()
{
    int index;
    int count = 0;

    for(index = 0; index < mpWiimoteArraySize; index++)
    {
        if((mpWiimoteArray[index]->state & 0x0008) != 0)
            count++;
    }

    return count;
}

CWiimote& CWii::GetByID(int UnID, int Refresh)
{
    std::vector<CWiimote>::iterator i;

    if(Refresh)
        RefreshWiimotes();

    for(i = mpWiimotesVector.begin(); i != mpWiimotesVector.end(); ++i)
    {
        if((*i).GetID() == UnID)
            return *i;
    }

    return *mpWiimotesVector.begin(); // Return the first one if it was not found.
}

std::vector<CWiimote>& CWii::GetWiimotes(int Refresh)
{
    if(Refresh)
        RefreshWiimotes();

    return mpWiimotesVector;
}

void CWii::SetBluetoothStack(CWii::BTStacks Type)
{
    wiiuse_set_bluetooth_stack((struct wiimote_t**) mpWiimoteArray, mpWiimoteArraySize, (win_bt_stack_t) Type);
}

void CWii::SetTimeout(int NormalTimeout, int ExpTimeout)
{
    wiiuse_set_timeout((struct wiimote_t**) mpWiimoteArray, mpWiimoteArraySize, NormalTimeout, ExpTimeout);
}

int CWii::Find(int Timeout)
{
    return wiiuse_find((struct wiimote_t**) mpWiimoteArray, mpWiimoteArraySize, Timeout);
}

std::vector<CWiimote>& CWii::Connect()
{
    int numConnected;
    int index;

    mpWiimotesVector.clear();

    numConnected = wiiuse_connect((struct wiimote_t**) mpWiimoteArray, mpWiimoteArraySize);

    for(index = 0; index < numConnected; index++)
    {
        CWiimote wm(mpWiimoteArray[index]);
        mpWiimotesVector.push_back(wm);
    }

    return mpWiimotesVector;
}

int CWii::Poll()
{
    return wiiuse_poll((struct wiimote_t**) mpWiimoteArray, mpWiimoteArraySize);
}
