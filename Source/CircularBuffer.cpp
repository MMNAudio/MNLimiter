/*
  ==============================================================================

    CircularBuffer.cpp
    Created: 29 Apr 2020 9:45:03am
    Author:  M

  ==============================================================================
*/

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer()
{
    buffer = AudioSampleBuffer();
    writeIndex = readIndex = delayLength = 0;
}

CircularBuffer::CircularBuffer(int _bufferSize, int _delayLength)
{
    buffer = AudioSampleBuffer(1, _bufferSize);
    buffer.clear();
    writeIndex = _delayLength;
    readIndex = 0;
    this->delayLength = _delayLength;
}

float CircularBuffer::GetData()
{
    return buffer.getSample(0, readIndex);
}

void CircularBuffer::SetData(float _data)
{
    buffer.setSample(0, writeIndex, _data);
}

void CircularBuffer::NextSample()
{
    int bufferLength = buffer.getNumSamples();
    readIndex = ((bufferLength + writeIndex) - delayLength) % bufferLength;
    writeIndex = (writeIndex + 1) % bufferLength;
}
