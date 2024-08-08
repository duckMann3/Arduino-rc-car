======================================================================================================================================

    DOCUMENTATION ABOUT THE "WIRE LIBRARY"

======================================================================================================================================
The Wire library is what Arduino uses to communicate with I2C devicces. It is included in all board packages, so you don't need to install it manually in order to use it.
======================================================================================================================================
Functions:

> begin() -- Initialise the I2C bus.
> end() -- Close the I2C bus.
> requestFrom() -- Request bytes from a peripheral device.
> beginTransmission() -- Begins queuing up a transmission.
> endTransmission() -- Transmit the bytes that have been queued and end the transmission.
> write() -- Writes data from peripheral to controller or vice versa.
> available() -- returns the number of bytes available for retrieval.
> read() -- Reads a byte that was transmitted from a peripheral to a controller.
> setClock() -- Modify the clock frequency.
> onReceive() -- Register a function to be called when a peripheral receives a transmission.
> onRequest() -- Registers a function to be called when a controller requests data.
> setWireTimeout() -- Sets the timeout for transmissions in controller mode.
> clearWireTimeoutFlag() -- Clears the timeout flag.
> getWireTimeoutFlag() -- Checks whether a timeout has occurred since the last time the flag was cleared.
