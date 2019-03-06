import React, { Component } from 'react'
import {Typography} from '@material-ui/core'
import {BigBanners} from 'components'
import {withStyles} from '@material-ui/core/styles'
import footerImg from './footer.png'
import facebookIcon from './facebook.png'
import twitterIcon from './twitter.png'
import youtubeIcon from './youtube.png'
import rssIcon from './rss.png'
import ppIcon from './pp.png'
import visaIcon from './visa.png'
import mcIcon from './mc.png'
import hzIcon from './hz.png'


const styles = theme => ({
  root:{
    minHeight:"100px",
    marginBottom:"20px"
  },
  links:{
    margin:"10px 0",    
    display:"flex",
  },
  social:{
    margin:"0",
    padding:"0",
    display:"flex",
    flexGrow:1,
  },
  social_a:{
    display:"flex",
    alignItems: "center",
    marginRight:"25px"
  },
  money:{
    margin:"0",
    padding:"0",
    display:"flex",
    alignItems: "center",
  },
  money_a:{
    display:"flex",
    alignItems: "center",
  },
  info:{
    display:'flex',
    alignItems:'center'
  },
  label:{
    flexGrow:1
  },
  conf:{
    display:"flex"
  },
  conf_ul:{
    display:"flex",
    margin:"0 30px 0 0",
    padding:0
  },
  conf_li:{
    cursor:"pointer",
    margin:"0 8px",
    '&:hover':{
      fontWeight:500,
      textDecoration:'underline'
    }
  }
})


class Footer extends Component {
  render() {
    const {classes} = this.props;
    return (
      <footer className={classes.root}>
        <section>
          <BigBanners/>
        </section>
        <div style={{backgroundColor:"#f2f6f9"}}>
          <section>
            <img src={footerImg} alt="" style={{width:"100%", height:"auto"}}/>
          </section>
        </div>


        <section>
          <div className={classes.links}>
            <ul  className={classes.social}>
              <li><a href="http://facebook.com" target="_blank"  className={classes.social_a}><img src={facebookIcon} alt="" style={{margin:15}}/>Facebook</a></li>
              <li><a href="http://twitter.com" target="_blank" className={classes.social_a}><img src={twitterIcon} alt="" style={{margin:15}}/>Twitter</a></li>
              <li><a href="http://youtube.com" target="_blank" className={classes.social_a}><img src={youtubeIcon} alt="" style={{margin:15}}/>YouTube</a></li>
              <li><a href="http://rss.com" target="_blank" className={classes.social_a}><img src={rssIcon} alt="" style={{margin:15}}/>Rss Feed</a></li>
            </ul>
            <ul  className={classes.money}>
              <li><a href="http://facebook.com" target="_blank"  className={classes.money_a}><img src={ppIcon} alt="" style={{margin:15}}/></a></li>
              <li><a href="http://twitter.com" target="_blank" className={classes.money_a}><img src={visaIcon} alt="" style={{margin:15}}/></a></li>
              <li><a href="http://youtube.com" target="_blank" className={classes.money_a}><img src={mcIcon} alt="" style={{margin:15}}/></a></li>
              <li><a href="http://rss.com" target="_blank" className={classes.money_a}><img src={hzIcon} alt="" style={{margin:15}}/></a></li>
            </ul>
          </div>
          <hr/>
          <div className={classes.info}>
            <div className={classes.label}>
              <Typography variant="caption">©2013 SoftMarket Mangento Store by emthemes.com</Typography>
            </div>
            <div className={classes.conf}>
              <ul className={classes.conf_ul}>
                <li ><Typography variant="caption" className={classes.conf_li}>EN</Typography></li>
                <li><Typography variant="caption" className={classes.conf_li}>FR</Typography></li>
                <li><Typography variant="caption" className={classes.conf_li}>ES</Typography></li>
              </ul>
              <ul className={classes.conf_ul}>
                <li><Typography variant="caption" className={classes.conf_li}>$</Typography></li>
                <li><Typography variant="caption" className={classes.conf_li}>€</Typography></li>
                <li><Typography variant="caption" className={classes.conf_li}>£</Typography></li>
              </ul>
            </div>
          </div>
        </section>
      </footer>
      
    )
  }
}
export default withStyles(styles)(Footer)