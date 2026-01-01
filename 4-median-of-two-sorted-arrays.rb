# @param {Integer[]} nums1
# @param {Integer[]} nums2
# @return {Float}
def find_median_sorted_arrays(nums1, nums2)
    # Ensure nums1 is the smaller array to minimize binary search range
    if nums1.length > nums2.length
        return find_median_sorted_arrays(nums2, nums1)
    end

    x = nums1.length
    y = nums2.length
    low = 0
    high = x

    while low <= high
        partition_x = (low + high) / 2
        partition_y = (x + y + 1) / 2 - partition_x

        max_left_x = (partition_x == 0) ? -Float::INFINITY : nums1[partition_x - 1]
        min_right_x = (partition_x == x) ? Float::INFINITY : nums1[partition_x]

        max_left_y = (partition_y == 0) ? -Float::INFINITY : nums2[partition_y - 1]
        min_right_y = (partition_y == y) ? Float::INFINITY : nums2[partition_y]

        if max_left_x <= min_right_y && max_left_y <= min_right_x
            # We have partitioned the arrays at the correct place
            if (x + y) % 2 == 0
                return ([max_left_x, max_left_y].max + [min_right_x, min_right_y].min) / 2.0
            else
                return [max_left_x, max_left_y].max.to_f
            end
        elsif max_left_x > min_right_y
            # We are too far on the right side for partition_x. Go on left side.
            high = partition_x - 1
        else
            # We are too far on the left side for partition_x. Go on right side.
            low = partition_x + 1
        end
    end

    0.0
end
