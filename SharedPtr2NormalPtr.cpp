#include <iostream>
using namespace std;

class ReferenceKeeper
{
public:
	ReferenceKeeper(int& v) :m_value(v) {};
	void SetReference(const int& v) { m_value = v; }
	int GetValue() { return m_value; }

private:
	int& m_value;
};

class ConstReferenceKeeper
{
public:
	ConstReferenceKeeper(const int& v) :m_value(v) {};
	int GetValue() { return m_value; }
private:
	const int& m_value;
};
typedef shared_ptr<ConstReferenceKeeper> ConstReferenceKeeperPtr;

int main()
{
	int initialValue = 1;
	ReferenceKeeper refKeeper(initialValue);
	ConstReferenceKeeperPtr cRefKeeperPtr;
	cout << "initial value is: " << refKeeper.GetValue() << endl;
	{
		shared_ptr<int> valuePtr = shared_ptr<int>(new int(2));

		refKeeper.SetReference(*valuePtr);
		cRefKeeperPtr.reset(new ConstReferenceKeeper(*valuePtr));

		cout << "within the scope of shared pointer: " << endl;
		cout << "the vaue is : " << refKeeper.GetValue() << endl;
		cout << "the cvaue is : " << cRefKeeperPtr->GetValue() << endl;

		valuePtr.reset();
	}

	{
		cout << "after the scope of shared pointer:" << endl;
		cout << "the vaue is : " << refKeeper.GetValue() << endl;
		cout << "the cvaue is : " << cRefKeeperPtr->GetValue() << endl;
	}
	return 0;
}