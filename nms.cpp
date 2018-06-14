std::vector<region_data> nms(std::vector<region_data> pred,std::vector<region_data> nms_pred,float thresh)
{
    std::vector<float>x1(pred.size());
    std::vector<float>y1(pred.size());
    std::vector<float>x2(pred.size());
    std::vector<float>y2(pred.size());
    std::vector<float>areas(pred.size());
    std::vector<data_idx>scoreid(pred.size());
    data_idx data_id;
    for (int in=0;in<pred.size();in++)
    {
        x1[in] = pred[in].x_left_upper;
        y1[in] = pred[in].x_right_upper;
        x2[in] = pred[in].x_left_down;
        y2[in] = pred[in].x_right_down;
        areas[in] = (x2[in] - x1[in] + 1) * (y2[in] - y1[in] + 1);
        data_id.score = pred[in].score;
        data_id.id = in;
        scoreid[in] = data_id;

    }
    

	std::sort(scoreid.begin(),scoreid.end(),compare_data_idx);
    std::vector<float>keep;
    std::vector<float>suppressed(pred.size());
    for (int _i=0;_i<pred.size();_i++)
    {
        int i = scoreid[_i].id;
        if(suppressed[i] == 1)
            continue;
        keep.push_back(i);
        nms_pred.push_back(pred[i]);
        float ix1 = x1[i];
        float iy1 = y1[i];
        float ix2 = x2[i];
        float iy2 = y2[i];
        float iarea = areas[i];
        for (int _j=_i+1;_j<pred.size();_j++)
        {
            int j = scoreid[_j].id;
            if(suppressed[j] == 1)E:\RTX_file\smoba_talkflow.xml
                continue;
			float xx1 = max(ix1, x1[j]);
            float yy1 = max(iy1, y1[j]);E:\RTX_file\smoba_talkflow.xml
            float xx2 = min(ix2, x2[j]);
            float yy2 = min(iy2, y2[j]);
            float w = max(0.0, xx2 - xx1 + 1);
            float h = max(0.0, yy2 - yy1 + 1);
            float inter = w * h;
            float ovr = inter / (iarea + areas[j] - inter);
            if(ovr >= thresh)
                {suppressed[j] = 1;}
        }
    }
    return nms_pred;
}
