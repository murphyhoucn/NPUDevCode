int example[5];
int* ptr = example;

example[2] = 10;
cout << "example[2] =" << example[2] << endl;

*(ptr + 2) = 20;
cout << "example[2] =" << example[2] << endl;

*(int*)((char*)ptr + 8) = 30; // 两次强制类型转换
cout << "example[2] =" << example[2] << endl;
// 这三行代码等价！ptr+2中的“2”并不是数值2，指针+2的时候会自动根据数据类型来计算实际的字节数。


int arr1[5]; // an array created on the stack
for (int i = 0; i < 5; i++)
{
    arr1[i] = i;
}

int* arr2 = new int[5]; // an array created on the heap
for (int i = 0; i < 5; i++)
{
    arr2[i] = i;
}
delete[] arr2;

// arr1的生命周期结束后，内存空间会被自动回收。
// arr2没有生命周期的概念，必须手动来释放。


class Entity
{
public:
	int array1[5];
	int* array2 = new int[5];

	Entity()
	{
		int count = sizeof(array1) / sizeof(int); // 4*5 / 4 = 5 
		cout << "count of array1 is " << count << endl;

		count = sizeof(array2) / sizeof(int); // 4 / 4 = 1
		cout << "count of array2 is " << count << endl;

		for (int i = 0; i < count; i++)
		{
			array1[i] = i; 
			array2[i] = i;
		}
			
	}
};


// error!
int array1Size = 5;
int array1[array1Size];

// error!
const int array1Size = 5;
int array1[array1Size];

// 使用static方法！
// right!
static const int array1Size = 5;
int array1[array1Size];

// 使用constexpr方法！
// 没搞懂？❓🎯

