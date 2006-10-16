//////////////////////////////////////////////////////////////////////////////
//    Copyright 2004, SenseGraphics AB
//
//    This file is part of H3D API.
//
//    H3D API is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    H3D API is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with H3D API; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//    A commercial license is also available. Please contact us at 
//    www.sensegraphics.com for more information.
//
//
/// \file PhantomHapticsDevice.h
/// \brief Header file for PhantomHapticsDevice.
///
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __PHANTOMHAPTICSDEVICE_H__
#define __PHANTOMHAPTICSDEVICE_H__

#include <HAPIHapticsDevice.h>
#define HAVE_OPENHAPTICS
#ifdef HAVE_OPENHAPTICS
#include <HD/hd.h>
#endif

namespace HAPI {

  /// \class PhantomHapticsDevice
  /// \brief Interface to all Phantom haptics devices from SensAble Technologies.
  /// Uses the HD API of OpenHaptics to interface to the haptics devices, so every
  /// device supported by OpenHaptics is supported by this class.
  class HAPI_API PhantomHapticsDevice: public HAPIHapticsDevice {
  public:
    /// Constructor.
    /// device_name is the name of the device, as defined in the 
    /// "Phantom Configuration" tool. A device_name of "" will use the first available
    /// device.
    PhantomHapticsDevice( string _device_name = "" ):
      device_name( _device_name ),
      device_handle( -1 ) {
    }

    /// Destructor.
    virtual ~PhantomHapticsDevice() {}


    /// Returns the HD device handle for this device.
    inline HHD getDeviceHandle() { 
      return device_handle;
    }

    /// Returns the name of the device.
    virtual const string &getDeviceName() {
      return device_name;
    }

  protected:
    /// Implementation of updateDeviceValues using HD API to get the values.
    virtual void updateDeviceValues( DeviceValues &dv, HAPITime dt );

    /// Implementation of sendOutput using HD API to send forces.
    virtual void sendOutput( DeviceOutput &dv,
                             HAPITime dt );

    /// Implementation of initHapticsDevice using HD API.
    virtual bool initHapticsDevice();

    /// Releases all resources allocated in initHapticsDevice. 
    virtual bool releaseHapticsDevice();

    /// Enable the device. Positions can be read and force can be sent.
    inline virtual ErrorCode enableDevice() {
      ErrorCode e = HAPIHapticsDevice::enableDevice();
      // Starting scheduler here instead of in initHapticsDevice since because
      // of random crashes when using OpenHapticsRenderer. Apparantly HL API does
      // not like the scheduler to have already been started when creating a new
      // HL context.
      hdStartScheduler();
      return e;
    }

    /// The device name for this device.
    string device_name;
    /// The OpenHaptics device handle for this device.
    HHD device_handle;

    /// Handle for the callback for rendering ForceEffects.  
    vector< HDCallbackCode > hd_handles; 
  };
}

#endif
