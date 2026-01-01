/**
 * Definition for singly-linked list.
 * class ListNode {
 * int val;
 * ListNode next;
 * ListNode(int x) {
 * val = x;
 * next = null;
 * }
 * }
 */
public class Solution {
    public boolean hasCycle(ListNode head) {
        if (head == null)
            return false;

        // Floyd's Cycle-Finding Algorithm (Tortoise and Hare)
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next; // Move slow 1 step
            fast = fast.next.next; // Move fast 2 steps

            if (slow == fast) {
                return true; // Cycle detected
            }
        }

        return false; // No cycle
    }
}
