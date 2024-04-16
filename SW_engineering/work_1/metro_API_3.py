import tkinter as tk
from tkinter import messagebox, scrolledtext
import requests

class SubwayArrivalInfoStrategy:
    def get_arrival_info(self, data):
        raise NotImplementedError()

class AllArrivalInfoStrategy(SubwayArrivalInfoStrategy):
    def get_arrival_info(self, data):
        info_text = "\n입력하신 역에 대한 실시간 지하철 도착 정보입니다!\n"
        for train_info in data['realtimeArrivalList']:
            train_line = train_info['trainLineNm']
            dest_station = train_info['statnNm']
            arrival_msg = train_info['arvlMsg2']
            updn_line = train_info['updnLine']

            info_text += "--------{}--------\n".format("상행선" if updn_line == "상행" else "하행선")
            info_text += f"도착 예정 열차: {train_line}행 - {dest_station}방면 - {arrival_msg}\n"

        return info_text

class ClosestArrivalInfoStrategy(SubwayArrivalInfoStrategy):
    def get_arrival_info(self, data):
        closest_train = min(data['realtimeArrivalList'], key=lambda x: x['barvlDt'])
        train_line = closest_train['trainLineNm']
        dest_station = closest_train['statnNm']
        arrival_msg = closest_train['arvlMsg2']
        updn_line = closest_train['updnLine']

        info_text = "\n가장 가까운 열차의 도착 정보입니다:\n"
        info_text += f"도착 예정 열차: {train_line}행 - {dest_station}방면 - {arrival_msg}\n"

        return info_text

class SubwayArrivalInfoContext:
    def __init__(self, strategy):
        self.strategy = strategy

    def execute_strategy(self, data):
        return self.strategy.get_arrival_info(data)

def get_subway_arrival_info(api_key, station, strategy):
    url = f"http://swopenapi.seoul.go.kr/api/subway/{api_key}/json/realtimeStationArrival/0/5/{station}"
    try:
        response = requests.get(url)
        data = response.json()

        context = SubwayArrivalInfoContext(strategy)
        return context.execute_strategy(data)

    except KeyError:
        return "입력한 역에 대한 정보를 가져올 수 없습니다."
    except Exception as e:
        return f"에러 발생: {e}"

def main():
    # tkinter 윈도우 생성
    window = tk.Tk()
    window.title("지하철 실시간 도착정보 프로그램")

    # API 키와 역 입력 위젯
    api_key_label = tk.Label(window, text="실시간 지하철 API 키를 입력하세요:")
    api_key_label.pack()
    api_key_entry = tk.Entry(window)
    api_key_entry.pack()

    station_label = tk.Label(window, text="확인할 지하철 역을 입력하세요:")
    station_label.pack()
    station_entry = tk.Entry(window)
    station_entry.pack()

    # 체크박스 생성
    checkbox_var = tk.StringVar()
    checkbox = tk.Checkbutton(window, text="모든 도착 정보 출력", variable=checkbox_var, onvalue="all", offvalue="")
    checkbox.pack()

    # 정보 출력창 생성
    output_text = scrolledtext.ScrolledText(window, wrap=tk.WORD, width=50, height=20)
    output_text.pack()

    def get_info():
        api_key = api_key_entry.get()
        station = station_entry.get()
        choice = checkbox_var.get()

        if not api_key or not station:
            messagebox.showwarning("경고", "API 키와 역을 모두 입력하세요.")
            return

        if choice == "all":
            strategy = AllArrivalInfoStrategy()
        else:
            strategy = ClosestArrivalInfoStrategy()

        info = get_subway_arrival_info(api_key, station, strategy)
        output_text.delete(1.0, tk.END)  # 이전 정보 삭제
        output_text.insert(tk.END, info)

    # 확인 버튼 생성
    button = tk.Button(window, text="정보 확인", command=get_info)
    button.pack()

    window.mainloop()

if __name__ == "__main__":
    main()
