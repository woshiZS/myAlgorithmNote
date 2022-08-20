#### 二分查找变种

* 起因是好几次自己需要用到普通二分的变种的时候忘记stl里面二分的正确使用方法，今天在来复习一下

* lower_bound

这个返回的是大于等于target的元素的第一个位置。

```c++
int lower_bound(vector<int>& a, int target){
    int l = 0, r = a.size();
    while(l < r){
        int mid = ((r - l) >> 1) + l;
        if(a[mid] >= target)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
```

* upper_bound

返回第一个大于给定元素的index

```c++
int upper_bound(vector<int>& a, int target){
    int l = 0, r = a.size();
    while(l < r){
        int mid = ((r - l) >> 1) + l;
        if(a[mid] > target)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
```

* binary_search

普通二分，找到则返回对应下标，否则返回-1.

```c++
int binary_search(vector<int>& a, int target){
    int l = 0, r = a.size() - 1;
    while(l <= r){
        int mid = ((r - l) >> 1) + l;
        if(a[mid] == target)
            return mid;
        else if(a[mid] > target)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}
```

具体的一些测试样例防到了同文件的bsearch.cpp文件中，这里算是对二分查找进行了一下复习巩固，以后遇到变种也能游刃有余。