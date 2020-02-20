from scipy.optimize import curve_fit
import urllib
import json
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import time


def date_encode(date):
    # '01.24' -> 1 * 100 + 24 = 124
    d = date.split('/')
    month, day = int(d[0]), int(d[1])
    return 100 * month + day


def date_decode(date):
    # 124 -> '01.24'
    return '{}.{}'.format(str(date // 100), str(date % 100))
    
    
def sequence_analyse(data):
    date_list, confirm_list, dead_list, heal_list, suspect_list = [], [], [], [], []
    data.sort(key = lambda x: date_encode(x['date']))
    for day in data:
        date_list.append(day['date'])
        confirm_list.append(int(day['confirm']))
        dead_list.append(int(day['dead']))
        heal_list.append(int(day['heal']))
        suspect_list.append(int(day['suspect']))
    return pd.DataFrame({
        'date': date_list, 
        'confirm': confirm_list, 
        'dead': dead_list,
        'heal': heal_list,
        'suspect': suspect_list
    })


def get_date_list(target_month = 3):
    """
    得到从1月13日到month月最后一天的所有日期列表
    """
    month_day = [0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    cur_month, cur_day = 1, 13
    ans = []
    while cur_month <= target_month:
        while cur_day <= month_day[cur_month]:
            d = "0" + str(cur_day) if cur_day < 10 else str(cur_day)
            ans += [str(cur_month) + "/" + d]
            cur_day += 1
        cur_day = 1
        cur_month += 1
    return ans


def logistic_function(t, K, P0, r):
    t0 = 0
    exp = np.exp(r * (t - t0))
    return (K * exp * P0) / (K + (exp - 1) * P0)

def predict():
    # 预测未来天数
    predict_days = 20
    
    # 获取实时数据
    url = 'https://view.inews.qq.com/g2/getOnsInfo?name=wuwei_ww_cn_day_counts'
    response = urllib.request.urlopen(url)
    json_data = response.read().decode('utf-8').replace('\n','')
    data = json.loads(json_data)
    data = json.loads(data['data'])
    df = sequence_analyse(data)
    date, confirm = df['date'].values, df['confirm'].values
    x = np.arange(len(confirm))
    date_labels = get_date_list(4)

    # 用最小二乘法估计拟合
    popt, pcov = curve_fit(logistic_function, x, confirm)
    print(popt)

    # 近期情况预测
    predict_x = list(x) + [x[-1] + i for i in range(1, 1 + predict_days)]
    predict_x = np.array(predict_x)
    predict_y = logistic_function(predict_x, popt[0], popt[1], popt[2])

    # 绘图
    plt.figure(figsize=(15, 8))
    
    # 绘制参考线
    for i in range(len(x), len(predict_x)):
        plt.plot([predict_x[0], predict_x[i]], [predict_y[i], predict_y[i]], color='#d2d2d2', linewidth=1)
        plt.plot([predict_x[i], predict_x[i]], [0, predict_y[i]], color='#d2d2d2', linewidth=1)
        
    plt.plot(x, confirm, 's',label="confimed infected number")
    plt.plot(predict_x, predict_y, 's',label="predicted infected number")
    plt.xticks(predict_x, date_labels[:len(predict_x) + 1], rotation=90)
    plt.yticks(rotation=90)

    plt.suptitle("Logistic Fitting Curve for 2019-nCov infected numbers(Max = {},  r={:.3})".format(int(popt[0]), popt[2]), fontsize=16, fontweight="bold")
    plt.title("Predict time:{}".format(time.strftime("%Y-%m-%d", time.localtime())), fontsize=16)
    plt.xlabel('date', fontsize=14)
    plt.ylabel('infected number', fontsize=14)
    plt.plot()
