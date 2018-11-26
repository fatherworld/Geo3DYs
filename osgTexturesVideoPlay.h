#ifndef OSGTEXTURES_H
#define OSGTEXTURES_H
#include "commHeader.h"
#include <osg/StateSet>

/*
 *osg模型发黑原因有3:
 * (1)osg中光照只会对有法线的模型起作用，而模型经过缩放后法线是不会变得，所以需要手动设置属性，。
 *  让法线随着模型大小变化而变化
 *  node->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
 *  (2)有些时候可能是光照的问题，有个笨办法是直接把模型的光照关闭
 *   node->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF| StateAttribute::OVERRIDE);
 * (3)如果模型始终是一面发黑一面正常，可能是只有平行光，需要设置个全局光。
 *
 */

//opencv中图像转osg图像需要注意opencv中的rb通道与osg中rb通道相反
static osg::ref_ptr<osg::Image> CVMat_2_OSGImage(cv::Mat& cvimg)
{
//    osg::Image osgframe2();
    osg::Image* osgframe = new osg::Image();
    osgframe->setImage(cvimg.cols, cvimg.rows, 3,
        GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, cvimg.data,
        osg::Image::NO_DELETE, 1);
    return osgframe;
}

//由四边形创建节点
void createNodeByQuad(osg::ref_ptr<osg::Geometry> geom)
{

    //设置顶点
    osg::ref_ptr<osg::Vec3Array> vc = new osg::Vec3Array();

    vc->push_back(osg::Vec3(0.0f,1.0f,0.0f));
    vc->push_back(osg::Vec3(1.0f,1.0f,0.0f));
    vc->push_back(osg::Vec3(1.0f,1.0f,-1.0f));
    vc->push_back(osg::Vec3(0.0f,1.0f,-1.0f));

    vc->push_back(osg::Vec3(0.0f,1.0f,-1.0f));
    vc->push_back(osg::Vec3(0.0f,1.0f,0.0f));
    vc->push_back(osg::Vec3(0.0f,0.0f,0.0f));
    vc->push_back(osg::Vec3(0.0f,0.0f,-1.0f));

    vc->push_back(osg::Vec3(0.0f,0.0f,0.0f));
    vc->push_back(osg::Vec3(1.0f,0.0f,0.0f));
    vc->push_back(osg::Vec3(1.0f,0.0f,-1.0f));
    vc->push_back(osg::Vec3(0.0f,0.0f,-1.0f));

    vc->push_back(osg::Vec3(0.0f,1.0f,-1.0f));
    vc->push_back(osg::Vec3(0.0f,0.0f,-1.0f));
    vc->push_back(osg::Vec3(1.0f,0.0f,-1.0f));
    vc->push_back(osg::Vec3(1.0f,1.0f,-1.0f));

    vc->push_back(osg::Vec3(1.0f,1.0f,-1.0f));
    vc->push_back(osg::Vec3(1.0f,0.0f,-1.0f));
    vc->push_back(osg::Vec3(1.0f,0.0f,0.0f));
    vc->push_back(osg::Vec3(1.0f,1.0f,0.0f));


    geom->setVertexArray(vc.get());

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,1.0f));
    vt->push_back(osg::Vec2(0.0f,1.0f));

    /*
    重新设置纹理坐标
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.5f,0.0f));
    vt->push_back(osg::Vec2(0.5f,0.5f));
    vt->push_back(osg::Vec2(0.0f,0.5f));
*/

    vt->push_back(osg::Vec2(1.0f,1.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,1.0f));

    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,1.0f));
    vt->push_back(osg::Vec2(0.0f,1.0f));

    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,1.0f));
    vt->push_back(osg::Vec2(0.0f,1.0f));

    vt->push_back(osg::Vec2(1.0f,1.0f));
    vt->push_back(osg::Vec2(0.0f,1.0f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));

    geom->setTexCoordArray(0,vt.get());


    //设置法线
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,20));

}


//
osg::ref_ptr<osg::Node> createNodeBy6Quad()
{
    //创建叶节点对象
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    //创建几何体对象

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    //创建顶点数组
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

    v->push_back(osg::Vec3(0.0f,0.0f,0.0f));
    v->push_back(osg::Vec3(1.0f,0.0f,0.0f));
    v->push_back(osg::Vec3(1.0f,0.0f,1.0f));
    v->push_back(osg::Vec3(0.0f,0.0f,1.0f));


    v->push_back(osg::Vec3(0.0f,1.0f,0.0f));
    v->push_back(osg::Vec3(1.0f,1.0f,0.0f));
    v->push_back(osg::Vec3(1.0f,1.0f,1.0f));
    v->push_back(osg::Vec3(0.0f,1.0f,1.0f));

    /*
    v->push_back(osg::Vec3(0.0f,0.0f,0.0f));
    v->push_back(osg::Vec3(0.0f,1.0f,0.0f));
    v->push_back(osg::Vec3(0.0f,1.0f,-1.0f));
    v->push_back(osg::Vec3(0.0f,0.0f,-1.0f));
    v->push_back(osg::Vec3(1.0f,1.0f,0.0f));
    v->push_back(osg::Vec3(1.0f,1.0f,-1.0f));
    v->push_back(osg::Vec3(1.0f,0.0f,0.0f));
    v->push_back(osg::Vec3(1.0f,0.0f,-1.0f));
*/



    //设置顶点数据
    geom->setVertexArray(v.get());

    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,8));

    //绘制
    geode->addDrawable(geom.get());

    return geode.get();
}


//由三角形创建节点
void createNodeByTriangle(osg::ref_ptr<osg::Geometry> geom)
{
 //   osg::ref_ptr<osg::Geode> geode = new osg::Geode();

//  osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    //设置顶点
    osg::ref_ptr<osg::Vec3Array> vc = new osg::Vec3Array();

    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(-1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, -0.09f));
    vc->push_back(osg::Vec3(0.32f,0.5f,-0.5f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));

    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, -0.09f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(1.0f, -0.5f, 0.5f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));


    /*
    vc->push_back(osg::Vec3(1.0f,0.0f,1.0f));
    vc->push_back(osg::Vec3(0.0f,0.0f,1.0f));
    vc->push_back(osg::Vec3(0.0f,0.0f,0.0f));
*/

    /*华为会议室顶点坐标*/
/*
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, -0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, -0.5f));
    vc->push_back(osg::Vec3(-1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(-1.0f, -0.5f, 0.375f));
*/
 /*
    vc->push_back(osg::Vec3(1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, 0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, 0.5f));
    vc->push_back(osg::Vec3(0.32f, 0.5f, 0.5f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, 0.375f));
    vc->push_back(osg::Vec3(1.0f, 0.5f, 0.375f));
*/
    geom->setVertexArray(vc.get());

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    geom->setTexCoordArray(0,vt.get());
/*
    vt->push_back(osg::Vec2(0.0f,0.875f));
    vt->push_back(osg::Vec2(0.66f,0.44f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,0.875f));
*/





    vt->push_back(osg::Vec2(0.0f,0.875f));
    vt->push_back(osg::Vec2(0.66f,0.44f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.66f,0.125f));
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(0.0f,0.875f));

    vt->push_back(osg::Vec2( 0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(1.0f,0.29f));
    vt->push_back(osg::Vec2(0.66f,0.0f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));

    vt->push_back(osg::Vec2(0.66f, 0.44f));
    vt->push_back(osg::Vec2(1.0f, 0.59f));
    vt->push_back(osg::Vec2(1.0f, 1.0f));
    vt->push_back(osg::Vec2( 1.0f, 1.0f));
    vt->push_back(osg::Vec2(0.0f, 0.875f));
    vt->push_back(osg::Vec2(0.66f, 0.44f));

    /*
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,1.0f));
*/





    //设置法线
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,18));
/*
    //绘制
    geode->addDrawable(geom.get());

    return geode.get();
*/
}



//创建二维纹理状态对象
osg::ref_ptr<osg::StateSet> createTexture2DState(osg::ref_ptr<osg::Image> image)
{

    //创建状态集对象

    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
    //创建二维纹理对象

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();

    texture->setDataVariance(osg::Object::DYNAMIC);

    //设置贴图
    texture->setImage(image.get());

    stateset->setTextureAttributeAndModes(0,texture.get(),osg::StateAttribute::ON);

    return stateset.get();
}


void play6Quad()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    osg::ref_ptr<osg::Group> root = new osg::Group();

    //添加到场景
    root->addChild(createNodeBy6Quad());

    //优化场景数据
    osgUtil::Optimizer optimizer;

    optimizer.optimize(root.get());

    viewer->setSceneData(root.get());

    viewer->realize();

    viewer->run();


}




void ShowTranImage()
{
    osg::ref_ptr<osg::DrawPixels> bitmap1 = new osg::DrawPixels;

    bitmap1->setPosition(osg::Vec3(0.0, 0.0, 0.0));


    string imageys = "F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\images\\beauty.jpg";

    Mat src = imread(imageys.c_str());

    /*
    string videoys = "F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\images\\m.avi";
    VideoCapture ys(videoys.c_str());
    Mat src;
*/


//    Mat src = imread(imageys.c_str());
#if 1
    osg::ref_ptr<osg::Image> image = CVMat_2_OSGImage(src);

    bitmap1->setImage(image);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    geode->addDrawable(bitmap1.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(geode.get());

    viewer.run();
#else


#endif
}


//通过回调函数进行视频帧的贴图，走通
class tankNodeCallbacks : public osg::NodeCallback
{
private:
    int count;
    Mat frame;
    Mat resizeDsts;
    osg::ref_ptr<osg::Image> image;
    osg::ref_ptr<osg::Texture2D> yss;
    VideoCapture* ys;
    osg::ref_ptr<osg::StateSet> stateset;
    osg::ref_ptr<osg::Image> signal_image;
public:
    tankNodeCallbacks::tankNodeCallbacks(/*osg::ref_ptr<osg::Image> image*/string localPath)
    {
       yss = new osg::Texture2D();

       yss->setDataVariance(osg::Object::DYNAMIC);
#if 0
       ys = new VideoCapture(0);
#else
       ys = new VideoCapture(localPath);
#endif
     //  this->count =  count;
     //  signal_image =  image;

       stateset = new osg::StateSet();
    }

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {

        osg::ref_ptr<osg::Geode> my = dynamic_cast<osg::Geode*>(node);
        if(my)
        {
            (*ys)>>frame;
            stateset = my->getStateSet();

            yss = dynamic_cast<osg::Texture2D *>(stateset->getTextureAttribute(0,osg::StateAttribute::TEXTURE)->asTexture());
            if (yss)
            {
                #if 0
                imshow("res",frame);
                waitKey(1);
#endif
         //   cv::resize(frame,resizeDsts,Size(2048,1024),0, 0, INTER_LINEAR);
            image =  CVMat_2_OSGImage(frame);
            if(image)
            {
                cout<<"image is not NULL"<<endl;
            }
            yss->setImage(image.get());
          //  yss->setImage(signal_image.get());
            cout<<"hello world"<<endl;
            }
            else
            {
                 cout<<"current count is"<<count<<endl;
            }


        }


   }
};




void playTexture()
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    osg::ref_ptr<osg::Group> root = new osg::Group();

    string videoys = "F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\images\\4.mp4";
    string imageys = "F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\images\\ys.jpg";
    string imag2 = "F:\\software\\vs2015_workplace\\qt\\TestProgramTeam\\images\\.jpg";

#if 0
    //读取贴图文件(图像文件)
    osg::ref_ptr<osg::Image> image2 = osgDB::readRefImageFile(imag2);

    osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile(imageys);
#else
    osg::ref_ptr<osg::Image> image2 = osgDB::readRefImageFile(imageys);
#endif
//    osg::ref_ptr<osg::Node> node = createNodeByQuad();
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    createNodeByTriangle(geom.get());
 //   createNodeByQuad(geom.get());

    geode->addDrawable(geom.get());

    osg::ref_ptr<osg::StateSet>stateset = createTexture2DState(image2.get());

    //使用二维纹理
    geode->setStateSet(stateset.get());

    geode->setUpdateCallback(new tankNodeCallbacks(videoys));



    //osg模型发黑(光照的问题，直接把模型的光照关闭)
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);



    osg::ref_ptr < osg::Node> b25 = osgDB::readNodeFile("C:\\osg\\osgmake\\osgearth_bin\\data\\cow.osg") ;

    // 对模型进行变换

    osg::ref_ptr < osg::MatrixTransform> scale = new osg::MatrixTransform ;

    scale ->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(0.0), 0, 0, 0)*osg::Matrix::scale(1.0,1.0,1.0)*osg::Matrix::translate(500, 0, 0)) ;



#if 1
    root->addChild(geode.get());
#else
    root->addChild(b25.get());
#endif

    //优化场景数据
    osgUtil::Optimizer optimizer;

    optimizer.optimize(root.get());

    viewer->setSceneData(root.get());

    osg::Matrix mt;
    mt.makeIdentity();

/*
    while(!viewer->done())
    {
        viewer->getCamera()->setViewMatrix( mt);

        viewer->frame();
 */

/*
    {
             osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
             traits->x = 40;
             traits->y = 40;
             traits->width = 600;
             traits->height = 480;
             traits->windowDecoration = true;
             traits->doubleBuffer = true;
             traits->sharedContext = 0;

             osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

             osg::ref_ptr<osg::Camera> camera = new osg::Camera;
             camera->setGraphicsContext(gc.get());
             camera->setViewport(new osg::Viewport(0,0, traits->width, traits->height));
             GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
             camera->setDrawBuffer(buffer);
             camera->setReadBuffer(buffer);

             // add this slave camera to the viewer, with a shift left of the projection matrix
             viewer->addSlave(camera.get());
         }
         */
    viewer->realize();

    viewer->run();

}

#endif // OSGTEXTURES_H
