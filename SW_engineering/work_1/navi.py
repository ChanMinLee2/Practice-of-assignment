import requests
from abc import ABC, abstractmethod

class Transportation(ABC):
    @abstractmethod
    def get_route(self, origin, destination):
        pass

class Walking(Transportation):
    def get_route(self, origin, destination):
        # 도보 경로 계산 및 예상 시간을 최우선 고려하여 반환
        return "Walking route from {} to {}.".format(origin, destination)

class Bus(Transportation):
    def get_route(self, origin, destination):
        # 버스 경로 계산 및 예상 시간을 최우선 고려하여 반환
        return "Bus route from {} to {}.".format(origin, destination)

class Subway(Transportation):
    def get_route(self, origin, destination):
        # 지하철 경로 계산 및 예상 시간을 최우선 고려하여 반환
        return "Subway route from {} to {}.".format(origin, destination)

class TransportationFactory(ABC):
    @abstractmethod
    def create_transportation(self):
        pass

class WalkingFactory(TransportationFactory):
    def create_transportation(self):
        return Walking()

class BusFactory(TransportationFactory):
    def create_transportation(self):
        return Bus()

class SubwayFactory(TransportationFactory):
    def create_transportation(self):
        return Subway()

class Navigator:
    def __init__(self, transportation_factory):
        self.transportation = transportation_factory.create_transportation()

    def plan_route(self, origin, destination):
        return self.transportation.get_route(origin, destination)

# 예제 사용
def main():
    # 사용자가 선택한 교통 수단에 따라 적절한 팩토리를 생성하여 네비게이터 객체를 생성합니다.
    transportation_type = input("Enter transportation type (walking/bus/subway): ")
    if transportation_type == "walking":
        factory = WalkingFactory()
    elif transportation_type == "bus":
        factory = BusFactory()
    elif transportation_type == "subway":
        factory = SubwayFactory()
    else:
        print("Invalid transportation type.")
        return

    navigator = Navigator(factory)
    origin = input("Enter origin: ")
    destination = input("Enter destination: ")
    route = navigator.plan_route(origin, destination)
    print("Route:", route)

if __name__ == "__main__":
    main()
