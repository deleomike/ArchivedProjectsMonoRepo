from .sizes import Size


class Vehicle:

    def __init__(self, size, license_plate):

        self.size = size
        self.license_plate = license_plate


class Motorcycle(Vehicle):

    def __init__(self, license_plate):
        super().__init__(Size.SMALL, license_plate)


class Sedan(Vehicle):

    def __init__(self, license_plate):
        super().__init__(Size.MEDIUM, license_plate)


class PickupTruck(Vehicle):

    def __init__(self, license_plate):
        super().__init__(Size.LARGE, license_plate)


class Bus(Vehicle):

    def __init__(self, license_plate):
        super().__init__(Size.XLARGE, license_plate)