// index.js
// 获取应用实例
const app = getApp()
const { connect } = require("../../utils/mqtt")
var amapFile = require('../../utils/amap-wx.130.js');
//var amapFile = require('https://unpkg.com/mqtt/dist/mqtt.min.js');

const mqttHost = '8.130.49.230'//mqtt服务器域名ip

//const mqttHost = 't91ba38d.ala.cn-hangzhou.emqxsl.cn'//mqtt服务器域名ip
const mqttPort = 8084//mqtt服务器域名ip
const deviceSubTopic = '/mysmarthome/sub'//设备订阅Topic（小程序发布命令topic）
const devicePubTopic = '/mysmarthome/pub'//设备发布Topic（小程序订阅数据topic）
const mpSubTopic = devicePubTopic
const mpPubTopic = deviceSubTopic
//天气

Page({
  data: {
    client:null,
    Temp:0,
    Hum:0,
    SoilHum:0,
    Light:0,
    Co2:0,
    TVOC:0,
    LED1:false,
    BUZZ:false,
    Servo:false,
    Fan:false,
    WaterPump:false,
    AutoControl:false,

    //天气
    province : "河南省",
    city : "郑州市",
    weather : "晴",
    temperature : 10,
    winddirection :  "西北",
    windpower : "≤5",
  },
  onLedChange(event){
    const that = this
    console.log(event.detail.value)
    const sw = event.detail.value
    that.setData({LED1:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"LED1",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开LED1指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"LED1",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭LED1指令')
        }
      })
    }
  },

  onBuzzChange(event){
    const that = this
    console.log(event.detail.value)
    const sw = event.detail.value
    that.setData({BUZZ:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"BUZZ",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开蜂鸣器指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"BUZZ",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭蜂鸣器指令')
        }
      })
    }
  },

  AutoControlChange(event){
    const that = this
    console.log("AutoControl值为："+event.detail.value)
    const sw = event.detail.value
    that.setData({AutoControl:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"AutoControl",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开自动模式指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"AutoControl",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭自动模式指令')
        }
      })
    }
  },

  onFanChange(event){
    const that = this
    console.log("Fan："+event.detail.value)
    const sw = event.detail.value
    that.setData({Fan:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"Fan",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开风扇指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"Fan",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭风扇指令')
        }
      })
    }
  },

  onPumpChange(event){
    const that = this
    console.log("WaterPump："+event.detail.value)
    const sw = event.detail.value
    that.setData({WaterPump:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"WaterPump",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开水泵指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"WaterPump",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭水泵指令')
        }
      })
    }
  },

  onFanChange(event){
    const that = this
    console.log(event.detail.value)
    const sw = event.detail.value
    that.setData({Fan:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"Fan",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开风扇指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"Fan",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭风扇指令')
        }
      })
    }
  },

  onServoChange(event){
    const that = this
    console.log(event.detail.value)
    const sw = event.detail.value
    that.setData({Servo:sw})
    if(sw){
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"Servo",
        value:1
      }),function(err){
        if(!err){
          console.log('成功下发打开舵机指令')
        }
      })
    }else{
      that.data.client.publish(mpPubTopic,JSON.stringify({
        target:"Servo",
        value:0
      }),function(err){
        if(!err){
          console.log('成功下发关闭舵机指令')
        }
      })
    }
  },


  // 事件处理函数
  onShow(){
    const that = this
    that.setData({
      //wxs实际上就是wss，wss实际上就是拥有SLL加密的WebSocket协议
      client:connect(`wxs://${mqttHost}:${mqttPort}/mqtt`),
      
    })
    that.data.client.on('connect',function(params){
     console.log("成功连接到MQTT服务器") 
     wx.showToast({
       title: '连接成功',
       icon: 'success',
       mask: true
     })
     that.data.client.on('error', (error) => {
      console.log('连接失败', error)
    })
     that.data.client.subscribe(mpSubTopic,function(err){
      if(!err){
        console.log('成功订阅设备上行数据Topic')
      } 
     })

    })
    that.data.client.on('message',function(topic,message){
      let dataFromDev = {}
      try {
        dataFromDev = JSON.parse(message)
        console.log(dataFromDev)
        that.setData({
          Temp:dataFromDev.Temp,
          Hum:dataFromDev.Hum,
          Light:dataFromDev.Light,
          LED1:dataFromDev.LED2,
          BUZZ:dataFromDev.BUZZ,
          SoilHum:dataFromDev.SoilHum,
          Servo:dataFromDev.Servo,
          Fan:dataFromDev.Fan,
          WaterPump:dataFromDev.WaterPump,
          Co2:dataFromDev.Co2,
          TVOC:dataFromDev.TVOC,
          AutoControl:dataFromDev.AutoControl,
        })
      } catch (error) {
        console.log('JSON解析失败',error)
      }
      // console.log(topic)
      // console.log(message)
      //message是16进制buffer字节流
      
    })
  },
  bindViewTap() {
    wx.navigateTo({
      url: '../logs/logs'
    })
  },
  onLoad() {
    
    if (wx.getUserProfile) {
      this.setData({
        canIUseGetUserProfile: true
      })
    }
    const that = this
    //天气预报
    var myAmapFun = new amapFile.AMapWX({key:'faeaa0d3d98fc04dd0b3e7f5ef54b4e5'});
    myAmapFun.getWeather({
      success: function(data){
        //成功回调
        console.log(data.liveData)
        that.setData({
          province : data.liveData.province,
          city : data.liveData.city,
          weather : data.liveData.weather,
          temperature : data.liveData.temperature,
          winddirection :  data.liveData.winddirection,
          windpower : data.liveData.windpower,
        }),
        console.log(data.liveData.city)
      },
      fail: function(info){
        //失败回调
        console.log(info)
      }
    })
  },
  getUserProfile(e) {
    // 推荐使用wx.getUserProfile获取用户信息，开发者每次通过该接口获取用户个人信息均需用户确认，开发者妥善保管用户快速填写的头像昵称，避免重复弹窗
    wx.getUserProfile({
      desc: '展示用户信息', // 声明获取用户个人信息后的用途，后续会展示在弹窗中，请谨慎填写
      success: (res) => {
        console.log(res)
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true
        })
      }
    })
  },
  getUserInfo(e) {
    // 不推荐使用getUserInfo获取用户信息，预计自2021年4月13日起，getUserInfo将不再弹出弹窗，并直接返回匿名的用户个人信息
    console.log(e)
    this.setData({
      userInfo: e.detail.userInfo,
      hasUserInfo: true
    })
  }
})
