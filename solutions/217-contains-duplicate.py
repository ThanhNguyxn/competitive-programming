class Solution:
    def containsDuplicate(self, nums: list[int]) -> bool:
        # A set contains only unique elements.
        # If the length of the set is less than the length of the list,
        # it means there were duplicates.
        return len(set(nums)) < len(nums)
