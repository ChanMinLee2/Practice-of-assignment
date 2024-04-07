import abc
import requests

class SubwayStrategy(abc.ABC):
    @abc.abstractmethod
    def get_train_info(self, data):
        pass

class AllTrainsStrategy(SubwayStrategy):
    def get_train_info(self, data):
        train_info_list = []
        for train_info in data['realtimeArrivalList']:
            train_line = train_info['trainLineNm']
            dest_station = train_info['statnNm']
            arrival_msg = train_info['arvlMsg2']
            updn_line = train_info['updnLine']

            train_info_list.append((train_line, dest_station, arrival_msg, updn_line))
        return train_info_list

class NearestUpboundTrainStrategy(SubwayStrategy):
    def get_train_info(self, data):
        nearest_upbound_train = None
        min_distance = float('inf')
        for train_info in data['realtimeArrivalList']:
            if train_info['updnLine'] == '상행':
                distance = int(train_info['barvlDt'])
                if distance < min_distance:
                    min_distance = distance
                    nearest_upbound_train = train_info
        if nearest_upbound_train:
            return [(nearest_upbound_train['trainLineNm'], nearest_upbound_train['statnNm'], nearest_upbound_train['arvlMsg2'], nearest_upbound_train['updnLine'])]
        else:
            return []

def get_subway_arrival_info(api_key, station, strategy):
    url = f"http://swopenapi.seoul.go.kr/api/subway/{api_key}/json/realtimeStationArrival/0/5/{station}"
    try:
        response = requests.get(url)
        data = response.json()
        print("\n입력하신 역에 대한 실시간 지하철 도착 정보입니다!")
        train_info_list = strategy.get_train_info(data)
        for train_info in train_info_list:
            train_line, dest_station, arrival_msg, updn_line = train_info
            print("--------{}--------".format("상행선" if updn_line == "상행" else "하행선"))
            print(f"도착 예정 열차: {train_line}행 - {dest_station}방면 - {arrival_msg}")
    except KeyError:
        print("입력한 역에 대한 정보를 가져올 수 없습니다.")
    except Exception as e:
        print(f"에러 발생: {e}")

def main():
    print("안녕하세요! 지하철 실시간 도착정보 프로그램입니다.")
    print("API 키와, 정보를 검색하실 역의 호선과 이름을 입력해주세요.\n")
    api_key = input("실시간 지하철 API 키를 입력하세요: ")
    station = input("확인할 지하철 역을 입력하세요: ")

    # 전략 선택
    print("\n사용하실 전략을 선택해주세요:")
    print("1. 모든 열차 정보 출력")
    print("2. 가장 가까운 상행열차 정보만 출력")
    strategy_choice = input("전략을 선택하세요 (1 또는 2): ")

    if strategy_choice == "1":
        strategy = AllTrainsStrategy()
    elif strategy_choice == "2":
        strategy = NearestUpboundTrainStrategy()
    else:
        print("잘못된 선택입니다.")
        return

    get_subway_arrival_info(api_key, station, strategy)

if __name__ == "__main__":
    main()
