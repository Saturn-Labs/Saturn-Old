#pragma once

namespace Saturn
{
	struct Time
	{
		Time(float time = 0.0f)
			: m_Time(time)
		{
		}

		inline float GetSeconds() const
		{
			return m_Time;
		}

		inline float GetMilliseconds() const
		{
			return m_Time * 1000.0f;
		}

		inline operator float() const
		{
			return m_Time;
		}

	private:
		float m_Time;
	};
}