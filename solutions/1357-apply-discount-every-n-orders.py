class Cashier(object):

    def __init__(self, n, discount, products, prices):
        """
        :type n: int
        :type discount: int
        :type products: List[int]
        :type prices: List[int]
        """
        self.n = n
        self.discount = discount
        self.count = 0
        self.price_map = {}
        for i in range(len(products)):
            self.price_map[products[i]] = prices[i]

    def getBill(self, product, amount):
        """
        :type product: List[int]
        :type amount: List[int]
        :rtype: float
        """
        self.count += 1
        
        total = 0
        for i in range(len(product)):
            total += amount[i] * self.price_map[product[i]]
        
        if self.count == self.n:
            # Use 100.0 to ensure float division in Python 2
            total = total * (100 - self.discount) / 100.0
            self.count = 0
        
        return float(total)
