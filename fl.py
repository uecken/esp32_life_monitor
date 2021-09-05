from flask import Flask,request,render_template
app = Flask(__name__)

# @app.route('/')
# def hello_world():
#     return "Hello Flask"

#http://35.76.198.152/output?id=id&sensor=sensor
@app.route('/output', methods=['GET','POST'])
def output():
    try:
        if request.method == 'GET':
            get = request.args.get('query','')
            if get=='get_json' :
                return {"key":"value","ket2":"value2"}
            else:
                id = request.args.get('id','')
                sensor = request.args.get('sensor','')
                return id +','+ sensor
        elif request.method == 'POST':
            pass
        #   post_rcv = request.form['query']
        #   return post_rcv
        else:
            return abort(400)
    except Exception as e:
        return str(e)

    hoge = str(request.json['hoge'])
    return "test"

@app.route ('/data' ,methods=['GET'])
def send_data():
    json_data = {'json':{
        'key':'hoge',
        'key1':'apple',
        }
    }
    return json_data

@app.route("/")
def index():
    return render_template("./index.html")

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=80)
