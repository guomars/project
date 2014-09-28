#ifndef __COUNTER_H__
#define __COUNTER_H__

// ¼ÆÊ±Æ÷Àà
class Counter
{
public:	
	Counter() : m_fCounter(0.0f), m_fPeriod(0.0f) {}
public:
	void setPeriod(float fPeriod) { m_fPeriod = fPeriod; }
	float getPeriod() { return m_fPeriod; }

	void setCounter(float fCounter) { m_fCounter = fCounter; }
	float getCounter() { return m_fCounter; }

	void reset() { m_fCounter = 0.0f; }

	bool incCounter(float fCounter,bool bRepeat = true)
	{ 
		if(m_fCounter >= m_fPeriod)
			return false;
		m_fCounter += fCounter;
		bool bFull = (m_fCounter >= m_fPeriod) ? true : false;
		if(bFull && bRepeat) reset();
		return bFull;
	}

	static Counter* CreateCounter(float fPeriod)
	{
		Counter* pCounter = new Counter();
		pCounter->setPeriod(fPeriod);
		return pCounter;
	}

	static void DeleteCounter(Counter* pCounter)
	{
		if(pCounter)
		{
			delete pCounter;
		}
	}

protected:	
	float	m_fCounter;		
	float	m_fPeriod;		
};

#endif // __COUNTER_H__