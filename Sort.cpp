#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV) {
		if (pushV.size() != popV.size() || pushV.empty())
			return false;
		stack<int> data;
		for (int i = 0, j = 0; i < pushV.size(); ++i) {
			data.push(pushV[i]);
			while (j < popV.size() && data.top() == popV[j]) {
				data.pop();
				++j;
			}
		}
		if (data.empty())
			return true;
		else
			return false;
	}
};
int main() {
	vector<int> vec{ 1,2,3,4,5 };
	vector<int> ret{ 4,5,3,2,1 };
	Solution().IsPopOrder(vec, ret);

	return 0;
}