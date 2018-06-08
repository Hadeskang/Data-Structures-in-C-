#include<iostream>
#include <vector>

using namespace std;

void InserSort(vector<int> &vec) { // �������� ʱ�临�Ӷ�O(n^2), �ռ临�Ӷ�O(1);
	int i = 0, j = 0;
	for (i = 1; i < vec.size(); ++i) {
		j = i - 1;
		int ret = vec[i];
		while (j >= 0 && vec[j] > ret) {
			vec[j + 1] = vec[j];
			--j;
		}
		vec[j + 1] = ret;
	}
}

void ShellSort(vector<int> &vec) { //ϣ������ʱ�临�Ӷ�O(n^1.3)���ռ临�Ӷ�O(1); ���ȶ�����
	int dk = 0, i = 0, j = 0;
	for (dk = vec.size() / 2; dk >= 1; dk /= 2) {
		for (i = dk; i < vec.size(); ++i) {
			int ret = vec[i];
			for (j = i - dk; j >= 0 && vec[j] > ret; j -= dk)
				vec[j + dk] = vec[j];
			vec[j + dk] = ret;
		}
	}
}

void BubbleSort(vector<int> &vec) { //ð������ʱ�临�Ӷ�O(n^2),�ռ临�Ӷ�O(1);�ȶ�����
	for (int i = 0; i < vec.size(); ++i) {
		for (int j = 0; j < vec.size() - i - 1; ++j) {
			if (vec[j] > vec[j + 1])
				swap(vec[j], vec[j + 1]);
		}
	}
}

void BubbleSort1(vector<int> &vec) { //ð������ļ��Ż��汾
	for (int i = 0; i < vec.size(); ++i) {
		bool flag = true;
		for (int j = 0; j < vec.size() - 1 - i; ++j){
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
				flag = false;
			}
		}
		if (flag)
			return;
	}
}

void QuickSort(vector<int> &vec, int low, int high) { //��������ʱ�临�Ӷ�O(nlogn),�ռ临�Ӷ�O(nlogn)�����ȶ�����
	if (low >= high)
		return;
	int start = low, end = high;
	int ret = vec[start];
	while (start < end) {
		while (start < end && vec[end] >= ret)
			--end;
		vec[start] = vec[end];
		while (start < end && vec[start] <= ret)
			++start;
		vec[end] = vec[start];
	}
	vec[start] = ret;
	QuickSort(vec, low, start - 1);
	QuickSort(vec, start + 1, high);
}

void sort(vector<int> &vec) { //���������ں������������е�Ӧ��
	int begin = 0, current = 0, end = vec.size() - 1;
	while (current <= end) {
		if (vec[current] == 0) {
			swap(vec[begin], vec[current]);
			++begin;
			++current;
		}
		else if (vec[current] == 1)
			++current;
		else {
			swap(vec[current], vec[end]);
			--end;
		}
	}
}

void SelectSort(vector<int> &vec) { //ѡ������ʱ�临�Ӷ�O(n^2)���ռ临�Ӷ�O(1);���ȶ�����
	for (int i = 0; i < vec.size() - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < vec.size(); ++j) {
			if (vec[j] < vec[minIndex])
				minIndex = j;
		}
		swap(vec[minIndex], vec[i]);
	}
}

void AdjustMaxHeap(vector<int> &vec, int i, int len) { //�ѵ���
	int j = i * 2 + 1;
	while (j < len) {
		if (j + 1 < len && vec[j] < vec[j + 1])
			++j;
		if (vec[i] > vec[j])
			break;
		swap(vec[i], vec[j]);
		i = j;
		j = i * 2 + 1;
	}
}

void MakeHeap(vector<int> &vec, int len) { //����
	for (int i = vec.size() / 2 - 1; i >= 0; --i) {
		AdjustMaxHeap(vec, i, len);
	}
}

void HeapSort(vector<int> &vec) { //������ʱ�临�Ӷ�O(nlogn),�ռ临�Ӷ�O(nlogn)�����ȶ�����
	MakeHeap(vec, vec.size() - 1);
	for (int i = vec.size() - 1; i >= 0; --i) {
		swap(vec[i], vec[0]);
		AdjustMaxHeap(vec, 0, i);
	}
}

void Merge(vector<int> &vec, int low, int mid, int high) { //�ϲ�
	vector<int> temp;
	int i, j, k;
	for (k = low; k <= high; ++k)
		temp.push_back(vec[k]);
	for (i = 0, j = mid - low + 1, k = low; i <= mid - low && j <= high - low; ++k) {
		if (temp[i] < temp[j])
			vec[k] = temp[i++];
		else
			vec[k] = temp[j++];
	}
	while (i <= mid - low)
		vec[k++] = temp[i++];
	while (j <= mid - mid - 1)
		vec[k++] = temp[j++];
}

void MergeSort(vector<int> &vec, int low, int high) {//�鲢����ʱ�临�Ӷ�O(nlogn)���ռ临�Ӷ�O(n)���ȶ�����
	if (low < high) {
		int mid = low + (high - low) / 2;
		MergeSort(vec, low, mid);
		MergeSort(vec, mid + 1, high);
		Merge(vec, low, mid, high);
	}
}


int main()
{
	vector<int> vec{ 1,2,3,4,5,0 };
	MergeSort(vec, 0, vec.size() - 1);
	for (auto val : vec)
		cout << val << endl;

	return 0;
}
