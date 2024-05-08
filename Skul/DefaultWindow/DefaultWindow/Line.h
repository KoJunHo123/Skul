#pragma once


class CLine
{
private:
	Line m_line;

public:
	CLine();
	CLine(Vec2 _first, Vec2 _second);

	~CLine();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	Line Get_Line() { return m_line; }

	//bool CheckInLine(float _fX, float _fY);

	void Set_Line(Vec2 _first, Vec2 _second)
	{
		m_line.first = _first;
		m_line.second = _second;
	}
};

