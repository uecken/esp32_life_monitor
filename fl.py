from flask import Flask,request,render_template
import json
import datetime
app = Flask(__name__)


# personal_datas = [
#     {"id":1111,"status":"detected","date":"2021-09-02_17-32-30"},
#     {"id":1112,"status":"non-detected","date":"2021-09-02_17-32-60"}
# ]
personal_datas = {}
personal_datas['1111'] = {"status":"detected","date":"2021-09-02_17-32-30"}

print(personal_datas)
#print(json.loads(personal_datas))

#http://35.76.198.152/output?id=id&status=status
# @app.route('/output', methods=['GET','POST'])
# def output():
#     try:
#         if request.method == 'GET':
#             get = request.args.get('query','')
#             if get=='get_json' :
#                 return {"key":"value","ket2":"value2"}
#             else:#?id=xxxx%?status=xxxx
#                 id = request.args.get('id','')
#                 sensor = request.args.get('status','')
#                 return id +','+ sensor
#         elif request.method == 'POST':
#             pass
#         #   post_rcv = request.form['query']
#         #   return post_rcv
#         else:
#             return abort(400)
#     except Exception as e:
#         return str(e)

#     hoge = str(request.json['hoge'])
#     return "test"

@app.route ('/report' ,methods=['GET'])
def send_data():
    try:
        if request.method == 'GET':
            id = request.args.get('id','')
            status = request.args.get('status','')
            date_time_fmt = datetime.datetime.today().strftime("%Y/%m/%d %H:%M:%S")
            print(id,status,date_time_fmt)

            if id is None :
                pass
            else:
                print("return json")
                #personal_datas.append({'id':id,'status':status,'date':date_time_fmt}) //listでは無く辞書型を使う。
                personal_datas[id] = {'status':status,'date':date_time_fmt}
                print(personal_datas)
                return_json = {'json':{
                    'id':id,
                    'status':status,
                    'date':date_time_fmt
                    }
                }
                print(return_json)
                return return_json
            #if get=='get_json' :
            #    return {"key":"value","ket2":"value2"}
        else:
            # json_data = {'json':{
            #     'key':'hoge',
            #     'key1':'apple',
            #     }
            # }
            # return json_data
            pass

    except Exception as e:
        return str(e)
        
@app.route ('/monitor' ,methods=['GET'])
def monitor():
    try:
        if request.method == 'GET':
            #id = request.args.get('id','')
            return personal_datas
    except Exception as e:
        return str(e)

@app.route("/")
def index():
    return render_template("./server.html")
    

@app.route("/client.html")
def client():
    return render_template("./client.html")

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=80)
