"""
两数之和问题
给定一个数组和目标值，找出两个数的下标使其和等于目标值
"""

def two_sum(nums, target):
    """
    使用哈希表查找两数之和

    Args:
        nums: 整数数组
        target: 目标和

    Returns:
        包含两个下标的元组，如果没有找到返回 None
    """
    # 用字典存储数值及其对应的下标
    num_dict = {}

    for i, num in enumerate(nums):
        # 计算需要的补数
        complement = target - num

        # 如果补数已经存在字典中，说明找到了答案
        if complement in num_dict:
            return (num_dict[complement], i)

        # 将当前数及其下标存入字典
        num_dict[num] = i

    return None


def main():
    print("========== 两数之和 ==========")

    # 输入数组
    nums_str = input("请输入若干个整数（空格分隔）: ")
    nums = list(map(int, nums_str.split()))

    # 输入目标值
    target = int(input("请输入目标和: "))

    # 查找
    result = two_sum(nums, target)

    if result:
        i, j = result
        print(f"\n找到答案！")
        print(f"nums[{i}] = {nums[i]}")
        print(f"nums[{j}] = {nums[j]}")
        print(f"{nums[i]} + {nums[j]} = {target}")
    else:
        print(f"\n没有找到两个数使其和为 {target}")


if __name__ == "__main__":
    main()
