#pragma once

class Time {
private:
	static float m_DeltaTime;
	static float m_LastTime;
	static float m_CurrentTime;

public:
	static inline const float GetDeltaTime() { return m_DeltaTime; }

public:
	static void Init();
};