n = int(input())
nums = list(map(int, input().split()))
k = int(input())
reqs = list(map(int, input().split()))

def find(nums, x):
    left = 0
    right = len(nums)
    while left < right:
        mid = (left + right) // 2
        if nums[mid] < x:
            left = mid + 1
        else:
            right = mid

    return left

res = []
for req in reqs:
    l = find(nums, req)
    if l == n:
        res.append(f"{0} {n} {n}")
        continue

    r = find(nums, req + 1)

    if nums[l] == req:
        res.append(f"{1} {l} {r}")
    else:
        res.append(f"{0} {l} {r}")


print("\n".join(res))
