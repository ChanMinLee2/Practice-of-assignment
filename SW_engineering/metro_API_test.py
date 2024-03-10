import requests

def get_subway_arrival_info(api_key, station):
    # API 호출을 위한 URL 생성
    url = f"http://swopenapi.seoul.go.kr/api/subway/{api_key}/json/realtimeStationArrival/0/5/{station}"
    try:
        # API에 요청을 보내고 응답 받기
        response = requests.get(url)
        data = response.json()

        # 결과를 출력
        print(f"\n입력하신 역에 대한 실시간 지하철 도착 정보입니다!")
        for train_info in data['realtimeArrivalList']:
            train_line = train_info['trainLineNm']
            dest_station = train_info['statnNm']
            arrival_msg = train_info['arvlMsg2']
            updn_line = train_info['updnLine']

            print("--------{}--------".format("상행선" if updn_line == "상행" else "하행선"))
            print(f"도착 예정 열차: {train_line}행 - {dest_station}방면 - {arrival_msg}")
    except KeyError:
        # API 응답에 필요한 정보가 없는 경우
        print("입력한 역에 대한 정보를 가져올 수 없습니다.")
    except Exception as e:
        # 그 외의 예외 처리
        print(f"에러 발생: {e}")

def main():
    print("안녕하세요! 지하철 실시간 도착정보 프로그램입니다.")
    print("API 키와, 정보를 검색하실 역의 호선과 이름을 입력해주세요.\n")

    # 사용자 입력 받기
    api_key = input("실시간 지하철 API 키를 입력하세요: ")
    station = input("확인할 지하철 역을 입력하세요: ")

    # 실시간 도착 정보 가져오기
    get_subway_arrival_info(api_key, station)

if __name__ == "__main__":
    main()
