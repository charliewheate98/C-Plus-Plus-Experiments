#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool isAnagram(string& s, string& t)
{
	if (s.length() != t.length())
		return false;

	sort(s.begin(), s.end());
	sort(t.begin(), t.end());

	return (s == t ? true : false);
}

vector<int> findAnagrams(string s, string p)
{
	vector<int> indices;

	if (p.length() <= 0)
		return vector<int>();

	if (s == p)
	{
		indices.push_back(0);
		return indices;
	}

	int k = static_cast<int>(p.size());
	int start = 0;
	int end = start + k;

	for (auto i = 0; i < k; i++)
	{
		string c = s.substr(0, i);

		if (isAnagram(c, p)) indices.push_back(c[0]);
		else break;
	}

	while (end <= s.length() && start <= s.length() - k)
	{
		string current_window_str = s.substr(start, end);

		if (isAnagram(current_window_str, p))
			indices.push_back(start);

		start++;
	}

	return indices;
}

int binarySearchHelper(vector<int>& nums, int left, int right, int k)
{
	if (right >= left)
	{
		int mid = left + (right - left) / 2;

		if (nums[mid] == k) {
			return mid;
		}

		if (nums[mid] >= k) {
			return binarySearchHelper(nums, left, mid - 1, k);
		}

		return binarySearchHelper(nums, mid + 1, right, k);
	}

	return -1;
}

int main(int argc, char** argv)
{
	//vector<int> res = { 5,7,7,8,8,10 };
	//int result = binarySearchHelper(res, 0, res.size(), 8);
	//cout << result << endl;
	//cout << indices.size() << endl;

	string s = "cbacbabacd";
	vector<int> res = findAnagrams(s, "abc");

	for (auto i = 0; i < res.size(); i++) {
		cout << "[start index: " << res[i] << "]" << endl;
	}

	std::cin.get();
	return 0;
}